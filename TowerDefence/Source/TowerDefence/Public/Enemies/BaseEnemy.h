// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "AIController.h"
#include "EnemyInterface.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS(config = Game, Blueprintable)
class TOWERDEFENCE_API ABaseEnemy : public ACharacter, public IEnemyInterface
{
    GENERATED_BODY()

 public:
    ABaseEnemy();

protected:
    int MaxHealth;

    int Health;

    int Reward;

    bool bIsDead;

    AAIController* AIController;

public:    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
    UAnimMontage* DeathAnimation;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    UWidgetComponent* HealthBar;

protected:
    void BeginPlay() override;

    void UpdateHealthBar();

public:
    float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* Instigator, AActor* Target) override;

    void MoveToActor(AActor* Actor) override;

    void OnDied();

    void OnDieAnimationStop();
    
    UFUNCTION(BlueprintCallable, Category = Attributes)
    void SetHealth(int Health, int MaxHealth);

    int GetHealth() const override;

    bool IsDead() const override;

    int GetMaxHealth() const override;

    UFUNCTION(BlueprintImplementableEvent, Category = Attributes, meta = (DisplayName = OnHealthChanged))
    void BP_OnHealthChanged(int Health, int MaxHealth);

    UFUNCTION(BlueprintImplementableEvent, Category = State, meta = (DisplayName = OnDeath))
    void BP_OnDeath();
};
