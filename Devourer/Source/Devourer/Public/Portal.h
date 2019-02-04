// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "Snake.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class DEVOURER_API APortal : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category = "Portal")
    APortal* Destination;

    APortal();

    UFUNCTION()
    void OnOverlap(AActor* Portal, AActor* OtherActor);

    UFUNCTION(BlueprintCallable, Category = "Portal")
    void Teleport(ASnake* Snake);
};
