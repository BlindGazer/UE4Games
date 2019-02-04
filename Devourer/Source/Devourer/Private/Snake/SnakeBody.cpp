// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#include "SnakeBody.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Engine.h"

ASnakeBody::ASnakeBody()
{
    PrimaryActorTick.bCanEverTick = false;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Devourer/Snake/SM_Body"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetStaticMesh(ShipMesh.Object);
    Mesh->SetVisibility(false);
    Mesh->SetCastShadow(false);

    RootComponent = Mesh;
}

void ASnakeBody::Move(FVector Location, FRotator Rotation, int Size, int Speed, float Animation)
{
    if(!Mesh->IsVisible())
    {
        Mesh->SetVisibility(true);
    }
    
    const FVector CurrentLocation = GetActorLocation();
    const FRotator  CurrentRotation = GetActorRotation();

    bool bIsParentTeleport = FMath::Abs(FVector::Dist(Location, CurrentLocation)) > Size + Speed;
    if (bIsParentTeleport)
    {
        const FVector OffsetLocation = Rotation.RotateVector(FVector(Size, 0, 0));
        SetActorLocation(Location - OffsetLocation);
    }
    
    UKismetSystemLibrary::MoveComponentTo(
        Mesh, Location, Rotation,
        false, false, Animation, false,
        EMoveComponentAction::Type::Move,
        FLatentActionInfo(1, 1, nullptr, this));

    if (Child) 
    {
        Child->Move(CurrentLocation, CurrentRotation, Size, Speed, Animation);
    }
}

void ASnakeBody::SetChild(ASnakeBody* Body)
{
    Child = Body;
}
