// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "SnakeBody.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Snake.generated.h"

UCLASS()
class DEVOURER_API ASnake : public APawn
{
    GENERATED_BODY()

public:
    static const FName MoveRightBinding;
    static const FName MoveLeftBinding;
    static const FName SwitchCameraBinding;
    static const FName PauseBinding;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Movement")
    int Speed;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    float AnimationTime;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Snake")
    int SnakeSize;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Snake")
    float Points;

    UPROPERTY(BlueprintReadOnly, Category = "Snake")
    bool bIsLose;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snake")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmViewTop;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmThirdPerson;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Snake")
    UBoxComponent* Collision;
    
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class ASnakeBody> ToBodySpawn;

    ASnake();

    void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Events")
    void OnOverlap(AActor* Snake, AActor* OtherActor);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void MoveLeft();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void MoveRight();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Pause();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void SwitchCamera();

    UFUNCTION(BlueprintCallable, Category = "Spawn")
    void SpawnBody();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Eat(AFood* Food);

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Move();

    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Stop() const;
    
private:
    ASnakeBody* Last;
    ASnakeBody* Child;
    float CurrentRotation;
    float EndRotation;
    bool bIsViewTop;

    UFUNCTION()
    void EndMove();

    void BeginPlay() override;
};