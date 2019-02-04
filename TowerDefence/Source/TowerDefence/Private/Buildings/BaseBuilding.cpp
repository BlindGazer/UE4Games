// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "BaseBuilding.h"
#include "TowerDefence.h"
#include "UObject/ConstructorHelpers.h"
#include "NavAreas/NavArea_Obstacle.h"

ABaseBuilding::ABaseBuilding()
{
    BuildPlace = CreateDefaultSubobject<UBoxComponent>("BuildPlace");
    BuildPlace->bDynamicObstacle = true;
    BuildPlace->SetBoxExtent(FVector(64));
    BuildPlace->AreaClass = UNavArea_Obstacle::StaticClass();

    RootComponent = BuildPlace;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Game/TowerDefence/Buildings/Platforms/ST_Cube"));

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
    PlatformMesh->SetStaticMesh(StaticMeshFinder.Object);
    PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlatformMesh->AttachToComponent(BuildPlace, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABaseBuilding::Upgrade(ABaseTower * Tower)
{
	TowerComponent = Tower;
}
