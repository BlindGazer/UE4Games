// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once
#include "ProjectileAttributes.generated.h"

USTRUCT(BlueprintType)
struct FProjectileAttributes
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Attributes)
    int Damage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Attributes)
    int Radius;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Attributes)
    int Speed;
};