// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "FoodSpawner.generated.h"

UCLASS()
class DEVOURER_API AFoodSpawner : public AActor
{
    GENERATED_BODY()

public:
    AFoodSpawner();

    UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Spawn")
    class UBoxComponent* SpawningVolume;

    UPROPERTY(EditAnyWhere, Category = "Spawn")
    TSubclassOf<class AFood> ToFoodSpawn;

    UFUNCTION(BlueprintPure, Category = "Spawn")
    FVector GetRandomPointInVolume();
                                                            
    UFUNCTION(BlueprintPure, Category = "Spawn")
    AFood* Spawn();

    UFUNCTION(BlueprintCallable, Category = "Spawn")
    void DestroyedFood(AActor* Food);

protected:
    virtual void BeginPlay() override;
};
