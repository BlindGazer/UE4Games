// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "WavePoint.h"
#include "WaveSetting.h"
#include "TimerManager.h"
#include "WaveSpawner.generated.h"

UCLASS()
class TOWERDEFENCE_API AWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaveSpawner();

private:
    UWorld* World;
    FTimerManager* TimerManager;
    
    FVector GetRandomLocationInAvailableArea(bool bIsAir) const;

protected:
	virtual void BeginPlay() override;

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    UDecalComponent* Decal;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    UBoxComponent* AvailableArea;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = WaveSettings)
    TMap<uint8, FWaveSetting> WaveSettings;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    AWavePoint* Destionation;
    
    UFUNCTION(BlueprintCallable, Category = Waves)
    void SpawnWave(uint8 WaveNumber);

    UFUNCTION(BlueprintCallable, Category = Waves)
    void SpawnActor(TSubclassOf<AActor> Type, const FRotator& Rotation);

    UFUNCTION(BlueprintCallable, Category = Waves)
    void SpawnGroup(const FWaveGroupSetting& Setting, const FRotator& Rotation);

    UFUNCTION(BlueprintCallable, Category = Waves)
    void SpawnGroups(const FWaveSetting& Setting);
    
    UFUNCTION(BlueprintImplementableEvent, Category = Waves, meta = (DisplayName = OnActorSpawn))
    void BP_OnActorSpawn(AActor* Actor);
};
