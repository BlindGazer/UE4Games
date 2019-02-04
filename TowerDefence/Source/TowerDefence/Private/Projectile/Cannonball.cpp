// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "Cannonball.h"
#include "TowerDefence.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ACannonball::ACannonball()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SetStaticMeshFinder(TEXT("/Game/TowerDefence/Projectiles/SM_Cannonball")); 
    Mesh->SetStaticMesh(SetStaticMeshFinder.Object);
    Mesh->SetWorldScale3D(FVector(0.4, 0.4, 0.4));

    AdditionalLifeSpan = 0.1;
}

void ACannonball::LifeSpanExpired()
{
    DealDamage(this);

    Super::LifeSpanExpired();
}

void ACannonball::DealDamage(AActor* Target)
{
    if (Attributes.Damage > 0 && Attributes.Radius > 0)
    {
        UGameplayStatics::ApplyRadialDamageWithFalloff(
            Target, Attributes.Damage, Attributes.Damage/2, 
            Target->GetActorLocation(),
            Attributes.Radius, Attributes.Radius * 2, Attributes.Damage / 2, UDamageType::StaticClass(),
            TArray<AActor*>(), this);
    }
}
