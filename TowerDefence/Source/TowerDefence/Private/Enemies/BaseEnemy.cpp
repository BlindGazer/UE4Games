// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "BaseEnemy.h"
#include "TowerDefence.h"
#include "TowerDefenceGameState.h"
#include "TimerManager.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "HealthBarInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy() : 
    Super(), Health(0), MaxHealth(100)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
    HealthBar->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
    HealthBar->SetDrawSize(FVector2D(105, 16));
    HealthBar->SetRelativeLocation(FVector(0, 0, 120));
    HealthBar->SetRelativeRotation(FRotator(0, -90, 90));

    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}   

void ABaseEnemy::BeginPlay()
{
    if (Controller)
    {
        AIController = Cast<AAIController>(Controller);
    }

    Super::BeginPlay();
}

void ABaseEnemy::UpdateHealthBar()
{
    if (HealthBar)
    {
        auto Widget = HealthBar->GetUserWidgetObject();
        if (Widget && Widget->GetClass()->ImplementsInterface(UHealthBarInterface::StaticClass()))
        {
            IHealthBarInterface::Execute_OnUpdateHealth(Widget, Health, MaxHealth);
        }
    }
}

float ABaseEnemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* Instigator, AActor* Target)
{
    if (bIsDead)
    {
        return 0.f;
    }

    Damage = Super::TakeDamage(Damage, DamageEvent, Instigator, Target);

    if (Damage <= 0)
    {
        return 0.f;
    }

    auto NewHealth = FMath::Clamp((int)FMath::RoundHalfFromZero(Health - Damage), 0, MaxHealth);

    if (NewHealth == 0)
    {
        OnDied();
    }

    else if(NewHealth != Health)
    {
        Health = NewHealth;
        UpdateHealthBar();
        BP_OnHealthChanged(Health, MaxHealth);
    }

    return Damage;
}

void ABaseEnemy::MoveToActor(AActor* Actor)
{
    if (AIController)
    {
        AIController->MoveToActor(Actor);
    }
    else 
    {
        UE_LOG(LogGame, Log, TEXT("ABaseEnemy::MoveToActor Controller is empty"));
    }
}

int ABaseEnemy::GetHealth() const
{
    return Health;
}

bool ABaseEnemy::IsDead() const
{
    return bIsDead;
}

int ABaseEnemy::GetMaxHealth() const
{
    return MaxHealth;
}

void ABaseEnemy::OnDied()
{
    if (bIsDead || IsPendingKill())
    {
        return;
    }

    bIsDead = true;
    Health = 0;

    HealthBar->DestroyComponent();
    GetWorldTimerManager().ClearAllTimersForObject(this);

    auto const GameState = GetWorld()->GetGameState<ATowerDefenceGameState>();
    if (GameState)
    {
        GameState->OnEnemyDied(this);
    }

    auto Capsule = GetCapsuleComponent();
    if (Capsule)
    {
        Capsule->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Capsule->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
        Capsule->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
    }

    auto Movement = GetCharacterMovement();
    if (Movement)
    {
        Movement->StopMovementImmediately();
        Movement->DisableMovement();
    }

    if (Controller)
    {
        Controller->UnPossess();
    }
    
    BP_OnDeath();

    if (DeathAnimation)
    {
        float DeathAnimDuration = PlayAnimMontage(DeathAnimation) / (GetMesh() && GetMesh()->GlobalAnimRateScale > 0 ? GetMesh()->GlobalAnimRateScale : 1);
        FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseEnemy::OnDieAnimationStop, DeathAnimDuration -0.5, false);
    }
    else 
    {
        OnDieAnimationStop();
    }
}

void ABaseEnemy::OnDieAnimationStop()
{
    Destroy();
}

void ABaseEnemy::SetHealth(int Health, int MaxHealth)
{
    ABaseEnemy::Health = Health;
    ABaseEnemy::MaxHealth = MaxHealth;

    UpdateHealthBar();
    BP_OnHealthChanged(Health, MaxHealth);
}
