// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "Arbalest.h"
#include "TowerDefence.h"
#include "Arrow.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AArbalest::AArbalest()
{
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshFinder(TEXT("/Game/TowerDefence/Buildings/Towers/Arbalest/SM_Arbalest"));
	Mesh->SetSkeletalMesh(MeshFinder.Object);
    Mesh->SetRelativeScale3D(FVector(.5f));
    AttackArea->InitSphereRadius(800.0f);
    ProjectileSpeed = 2000;
	ProjectileClass = AArrow::StaticClass();
}