// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class DEVOURER_API AFood : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food")
    uint8  Points;

    AFood();

    UFUNCTION()
    void OnOverlap(AActor* Food, AActor* OtherActor);
};