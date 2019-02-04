// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/Pawn.h"
#include "PlayerCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TOWERDEFENCE_API APlayerCamera : public APawn
{
    GENERATED_BODY()
    
public:
    APlayerCamera();

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
    UCameraComponent* Camera;

    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
    USpringArmComponent* SpringArm;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Control)
    float MaxZoomIn;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Control)
    float MaxZoomOut;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Control)
    float MoveSpeed;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Control)
    float RotateSpeed;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Control)
    float ZoomSpeed;

    UFUNCTION(BlueprintCallable, Category = Control)
    void MoveRight(float Scale);

    UFUNCTION(BlueprintCallable, Category = Control)
    void MoveForward(float Scale);

    UFUNCTION(BlueprintCallable, Category = Control)
    void Zoom(float Scale);

    UFUNCTION(BlueprintCallable, Category = Control)
    void RotateRight(float Scale);

    UFUNCTION(BlueprintCallable, Category = Control)
    void Reset();

private:
    void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
};
