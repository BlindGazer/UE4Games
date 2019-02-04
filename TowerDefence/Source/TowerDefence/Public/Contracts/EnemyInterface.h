// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "Moveable.h"
#include "EnemyInterface.generated.h"

UINTERFACE(Blueprintable, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UEnemyInterface: public UMoveable
{
	GENERATED_BODY()
};


class TOWERDEFENCE_API IEnemyInterface: public IMoveable
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Navigation)
    virtual bool IsDead() const = 0;
    
    UFUNCTION(BlueprintCallable, Category = Attributes)
    virtual int GetHealth() const = 0;

    UFUNCTION(BlueprintCallable, Category = Attributes)
    virtual int GetMaxHealth() const = 0; 
};
