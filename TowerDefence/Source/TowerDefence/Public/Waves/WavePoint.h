// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "WavePoint.generated.h"

UCLASS()
class TOWERDEFENCE_API AWavePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWavePoint();
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    bool bIsFinish;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    AWavePoint* NextPoint;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    UDecalComponent* Decal;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Navigation)
    UBoxComponent* PointArea;

    UFUNCTION(BlueprintCallable, Category = Area)
    void OnEnterArea(AActor* Point, AActor* OtherActor);
};
