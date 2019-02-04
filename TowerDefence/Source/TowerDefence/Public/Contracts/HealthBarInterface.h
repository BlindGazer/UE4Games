// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "HealthBarInterface.generated.h"

class AActor;

UINTERFACE(MinimalAPI)
class UHealthBarInterface: public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENCE_API IHealthBarInterface
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HealthBar)
    void OnUpdateHealth(int Health, int MaxHealth);
};
