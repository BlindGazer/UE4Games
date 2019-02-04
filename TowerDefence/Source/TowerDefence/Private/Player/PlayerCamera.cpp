// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "PlayerCamera.h"
#include "TowerDefence.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

const FName MoveRightBinding("MoveRight");
const FName MoveForwardBinding("MoveForward");
const FName ZoomInBinding("ZoomIn");
const FName RotateRightBinding("RotateRight");
const FName ResetBinding("Reset");

APlayerCamera::APlayerCamera():
    MaxZoomIn(600),
    MaxZoomOut(1000),
    MoveSpeed(50),
    RotateSpeed(5),
    ZoomSpeed(50)
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    RootComponent = SpringArm;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
    Camera->SetRelativeRotation(FRotator(-55, 0, 0));
}

void APlayerCamera::MoveRight(float Scale)
{
    if (Scale == 0)
    {
        return;
    }

    FVector Delta = FVector(0, Scale * MoveSpeed, 0);
    Delta = GetActorRotation().RotateVector(Delta);
    SetActorRelativeLocation(GetActorLocation() + Delta);
}

void APlayerCamera::MoveForward(float Scale)
{
    if (Scale == 0)
    {
        return;
    }

    FVector Delta = FVector(Scale * MoveSpeed, 0, 0);
    Delta = GetActorRotation().RotateVector(Delta);
    SetActorRelativeLocation(GetActorLocation() + Delta);
}

void APlayerCamera::Zoom(float Scale)
{
    if (Scale == 0)
    {
        return;
    }

    FVector Location = Camera->GetRelativeTransform().GetLocation();
    Location.Z += Scale * ZoomSpeed;

    if (Location.Z <= -MaxZoomIn || Location.Z >= MaxZoomOut)
    {
        return;
    }

    Camera->SetRelativeLocation(Location);
}

void APlayerCamera::RotateRight(float Scale)
{
    if (Scale == 0)
    {
        return;
    }

    auto Delta = FRotator(0, Scale * RotateSpeed, 0);
    SetActorRotation(GetActorRotation() + Delta);
}

void APlayerCamera::Reset()
{
    SetActorRelativeRotation(FRotator::ZeroRotator);
    Camera->SetRelativeLocation(FVector::ZeroVector);
}

void APlayerCamera::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
    Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAxis(MoveRightBinding, this, &APlayerCamera::MoveRight);
    InputComponent->BindAxis(MoveForwardBinding, this, &APlayerCamera::MoveForward);
    InputComponent->BindAxis(ZoomInBinding, this, &APlayerCamera::Zoom);
    InputComponent->BindAxis(RotateRightBinding, this, &APlayerCamera::RotateRight);
    InputComponent->BindAction(ResetBinding, EInputEvent::IE_Pressed, this, &APlayerCamera::Reset);
}
