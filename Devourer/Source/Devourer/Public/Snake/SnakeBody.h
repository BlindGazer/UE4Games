// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "SnakeBody.generated.h"

UCLASS()
class DEVOURER_API ASnakeBody : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    ASnakeBody();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Move(FVector Location, FRotator Rotation, int Size, int Speed, float Animation);
    
    UFUNCTION(BlueprintCallable, Category = "Actions")
    void SetChild(ASnakeBody* Body);

private:
    ASnakeBody* Child;
};
