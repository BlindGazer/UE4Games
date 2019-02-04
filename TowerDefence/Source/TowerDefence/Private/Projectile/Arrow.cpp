// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "Arrow.h"
#include "TowerDefence.h"
#include "UObject/ConstructorHelpers.h"

AArrow::AArrow()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SetStaticMeshFinder(TEXT("/Game/TowerDefence/Projectiles/SM_Arrow")); 
    Mesh->SetStaticMesh(SetStaticMeshFinder.Object);
    Mesh->SetWorldScale3D(FVector(2, 2, 2));

    AdditionalLifeSpan = 0.02;
}