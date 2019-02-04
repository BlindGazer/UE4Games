// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "WaveSetting.generated.h"

USTRUCT(BlueprintType)
struct FWaveGroupSetting
{
	GENERATED_BODY()
	
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSetting)
    TSubclassOf<class AActor> GroupType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSetting)
    int GroupCount;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSetting)
    float DelayTime;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSetting)
    int RepeatCount;
};

USTRUCT(BlueprintType)
struct FWaveSetting
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSetting)
    TArray<FWaveGroupSetting> EnemiesGroups;
};