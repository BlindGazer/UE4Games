// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "BaseProjectile.h"
#include "Cannonball.generated.h"

UCLASS()
class TOWERDEFENCE_API ACannonball : public ABaseProjectile
{
    GENERATED_BODY()
        
public:
    ACannonball();

    void LifeSpanExpired() override;

protected:
    void DealDamage(AActor* Target) override;
};
