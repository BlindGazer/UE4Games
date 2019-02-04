// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

class ABaseTower;

UCLASS()
class TOWERDEFENCE_API ABaseBuilding : public AActor
{
    GENERATED_BODY()
    
public:
    ABaseBuilding();

public:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Building)
    UBoxComponent* BuildPlace;

    UPROPERTY(BLueprintReadWrite, EditDefaultsOnly, Category = Building)
    UStaticMeshComponent* PlatformMesh;
	
	UPROPERTY(BLueprintReadWrite, EditDefaultsOnly, Category = Tower)
	ABaseTower* TowerComponent;

	UFUNCTION(BlueprintCallable, Category = Tower)
	void Upgrade(ABaseTower* Tower);
};
