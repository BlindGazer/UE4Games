// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#include "Snake.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Food.h"

const FName ASnake::MoveRightBinding("Right");
const FName ASnake::MoveLeftBinding("Left");
const FName ASnake::SwitchCameraBinding("SwitchCamera");
const FName ASnake::PauseBinding("Pause");

ASnake::ASnake()
{
    PrimaryActorTick.bCanEverTick = true;
    ToBodySpawn = ASnakeBody::StaticClass();
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/Devourer/Snake/SM_Head"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetStaticMesh(ShipMesh.Object);
    Mesh->SetCastShadow(false);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    RootComponent = Mesh;

    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    Collision->SetRelativeLocation(FVector(40, 0, 0));
    Collision->SetBoxExtent(FVector(10, 50, 50));
    Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    Collision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    SpringArmViewTop = CreateDefaultSubobject<USpringArmComponent>("SpringArmViewTop");
    SpringArmThirdPerson = CreateDefaultSubobject<USpringArmComponent>("SpringArmThirdPerson");
    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

    SpringArmViewTop->SetupAttachment(Mesh);
    SpringArmViewTop->bAbsoluteRotation = true;
    SpringArmViewTop->TargetArmLength = 2000;
    SpringArmViewTop->RelativeRotation = FRotator(-80, 0, 0);
    SpringArmViewTop->RelativeLocation = FVector(0, 0, 100);

    SpringArmThirdPerson->SetRelativeLocationAndRotation(FVector(-750, 0, 750), FRotator(-40, 0, 0));
    SpringArmThirdPerson->SetupAttachment(Mesh);

    Camera->SetupAttachment(SpringArmThirdPerson);
    Camera->bUsePawnControlRotation = false;

    OnActorBeginOverlap.AddDynamic(this, &ASnake::OnOverlap);

    bIsViewTop = false;
    SnakeSize = Mesh->Bounds.GetBox().GetSize().X + 10;
    Speed = SnakeSize * 2;
    AnimationTime = (float)SnakeSize / Speed;

    ToBodySpawn = ASnakeBody::StaticClass();
}

void ASnake::BeginPlay()
{
    Super::BeginPlay();

    Move();
}

#pragma region Movement

void ASnake::Move()
{
    const FRotator Rotator = GetActorRotation();
    const FVector Location = GetActorLocation();

    FRotator NewRotator = Rotator;
    NewRotator.Yaw = EndRotation;

    const FVector OffsetLocation = NewRotator.RotateVector(FVector(SnakeSize, 0, 0));

    const FLatentActionInfo ActionInfo = FLatentActionInfo(1, 1, TEXT("EndMove"), this);
    
    UKismetSystemLibrary::MoveComponentTo(
        Mesh, Location + OffsetLocation, NewRotator,
        false, false, AnimationTime, false,
        EMoveComponentAction::Type::Move,
        ActionInfo);

    if (Child)
    {
        Child->Move(Location, Rotator, SnakeSize, Speed, AnimationTime);
    }
}

void ASnake::EndMove() 
{
    CurrentRotation = EndRotation;
    Move();
}

void ASnake::Stop() const
{
    UKismetSystemLibrary::MoveComponentTo(
        Mesh, FVector::ZeroVector, FRotator::ZeroRotator,
        false, false, 0, false,
        EMoveComponentAction::Type::Stop, 
        FLatentActionInfo());
}

void ASnake::MoveLeft()
{
    if (CurrentRotation - EndRotation < 90)
    {
        EndRotation -= 90;
        Move();
    }
}

void ASnake::MoveRight()
{
    if (EndRotation - CurrentRotation < 90)
    {
        EndRotation += 90;
        Move();
    }
}

#pragma endregion

#pragma region Spawner

void ASnake::SpawnBody()
{
    if (ToBodySpawn)
    {
        FRotator Rotator;
        FVector Location;

        if (Last)
        {
            Location = Last->GetActorLocation();
            Rotator = Last->GetActorRotation();
        }
        else
        {
            Location = GetActorLocation();
            Rotator = GetActorRotation();
        }

        UWorld* World = GetWorld();

        if (World)
        {
            auto Body = World->SpawnActor<ASnakeBody>(ToBodySpawn, Location, Rotator);

            if (Body)
            {
                if (Last) 
                {
                    Last->SetChild(Body);
                }
                else 
                {
                    Child = Body;
                }

                Last = Body;
            }
        }
    }
}

void ASnake::Eat(AFood* Food)
{
    Points += Food->Points;
    Speed += 20;

    AnimationTime = (float)SnakeSize / Speed;
    SpawnBody();
}

#pragma endregion

#pragma region Controls

void ASnake::SwitchCamera()
{
    USpringArmComponent* SpringArm = bIsViewTop ? SpringArmThirdPerson : SpringArmViewTop;
    Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
    bIsViewTop = !bIsViewTop;
}

void ASnake::Pause()
{
    UGameplayStatics::SetGamePaused(this, !UGameplayStatics::IsGamePaused(this));
}

void ASnake::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up "movement" bindings.
    InputComponent->BindAction(MoveLeftBinding, IE_Pressed, this, &ASnake::MoveLeft);
    InputComponent->BindAction(MoveRightBinding, IE_Pressed, this, &ASnake::MoveRight);

    // Set up "Game Play" bindings.
    InputComponent->BindAction(PauseBinding, IE_Pressed, this, &ASnake::Pause);
    InputComponent->BindAction(SwitchCameraBinding, IE_Pressed, this, &ASnake::SwitchCamera);
}

#pragma endregion

void ASnake::OnOverlap(AActor* Snake, AActor* OtherActor)
{
    const auto Food = Cast<AFood>(OtherActor);

    if (Food)
    {
        Eat(Food);
    }
    else
    {
        auto SnakeBody = Cast<ASnakeBody>(OtherActor);

        if (SnakeBody && SnakeBody->Mesh->IsVisible())
        {
            UE_LOG(LogTemp, Display, TEXT("You lose"))
            bIsLose = true;
        }
    }
}