// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "ProjectileAttributes.h"
#include "BaseProjectile.generated.h"

class ABaseBuilding;
class USphereComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class TOWERDEFENCE_API ABaseProjectile : public AActor
{
    GENERATED_BODY()
        
public:
    ABaseProjectile();

protected:
    bool bInitialized;

    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    float AdditionalLifeSpan;

    FProjectileAttributes Attributes;

    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    USphereComponent* Collision;

    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
    UProjectileMovementComponent* ProjectileMovement;

public:
    void Init(const FVector& Destination, const FProjectileAttributes& Attributes);

    UFUNCTION(BlueprintImplementableEvent, Category = Projectile, meta = (DisplayName = OnHit))
    void BP_OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
    virtual void DealDamage(AActor* Target);
};
