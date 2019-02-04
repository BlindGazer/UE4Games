// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#include "Food.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Snake.h"

AFood::AFood()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Devourer/Food/SM_Food"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetStaticMesh(ShipMesh.Object);
    Mesh->SetCastShadow(false);

    OnActorBeginOverlap.AddDynamic(this, &AFood::OnOverlap);

    Points = 5;
    PrimaryActorTick.bCanEverTick = false;
}

void AFood::OnOverlap(AActor * Food, AActor * OtherActor)
{
    if (Cast<ASnake>(OtherActor))
    {
        Destroy();
    }
}

