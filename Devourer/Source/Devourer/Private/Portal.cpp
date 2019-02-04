// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#include "Portal.h"
#include "SnakeBody.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

APortal::APortal()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetupAttachment(RootComponent);

    OnActorBeginOverlap.AddDynamic(this, &APortal::OnOverlap);
}

void APortal::OnOverlap(AActor* Portal, AActor* OtherActor)
{
    const auto Snake = Cast<ASnake>(OtherActor);

    if (Snake && Destination)
    {
        Destination->Teleport(Snake);
    }
}

void APortal::Teleport(ASnake* Snake)
{
    Snake->Stop();

    FVector PortalLocation = GetActorLocation(), 
        SnakeLocation = Snake->GetActorLocation();

    const auto GetOffsetSnakeSizeCoordinate = [Snake](const float &Coordinate)
    {
        return Coordinate - FMath::Sign(Coordinate) * Snake->SnakeSize;
    };

    auto bIsVerticalPortal = FMath::Abs(PortalLocation.X) > FMath::Abs(PortalLocation.Y);

    if(bIsVerticalPortal)
    {        
        SnakeLocation.X = GetOffsetSnakeSizeCoordinate(PortalLocation.X);
    }
    else
    {
        SnakeLocation.Y = GetOffsetSnakeSizeCoordinate(PortalLocation.Y);
    }

    Snake->SetActorLocation(SnakeLocation);
    Snake->Move();
}