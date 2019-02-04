// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "Cannon.h"
#include "TowerDefence.h"
#include "Cannonball.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

ACannon::ACannon()
{
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
        MeshFinder(TEXT("/Game/TowerDefence/Buildings/Towers/Cannon/SM_Cannon"));
	Mesh->SetSkeletalMesh(MeshFinder.Object);
    Mesh->SetRelativeScale3D(FVector(.5f));
    DamageRadius = 250;
    ProjectileSpeed = 600;
	ProjectileClass = ACannonball::StaticClass();
}