// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "BaseTower.generated.h"

class USphereComponent;
class ABaseProjectile;
class USoundBase;
class UAnimSequenceBase;

UCLASS()
class TOWERDEFENCE_API ABaseTower : public AActor
{
    GENERATED_BODY()
    
public:
    ABaseTower();

protected:
	UWorld* World;
	FTimerManager* TimerManager;
	FTimerHandle AttackTimer;

	TQueue<AActor*> Targets;
	bool bIsActive;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Projectile)
    TSubclassOf<ABaseProjectile> ProjectileClass;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
    USkeletalMeshComponent* Mesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack)
    USphereComponent* AttackArea;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
    USoundBase* FireSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
    UAnimSequenceBase* FireAnimation;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Attack)
    int DamageRadius;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Attack)
    float AttackSpeed;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Attack)
    int ProjectileSpeed;

    UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = Gameplay)
    float CreationTime;
    
    UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = Attack)
    int Damage;
    
    UFUNCTION(BlueprintCallable, Category = Attack)
    void OnAreaEnter(AActor* Area, AActor* Actor);

    UFUNCTION(BlueprintImplementableEvent, Category = Gameplay, meta = (DisplayName = OnCreated))
    void BP_OnCreated();

protected:
    void BeginPlay() override;

	virtual bool SpawnProjectile(AActor* Target) const;

	virtual void InitProjectile(ABaseProjectile* Projectile, AActor* Target) const;

	virtual void PlayAnimation() const;

	virtual void PlaySound() const;
	
	virtual void RotateTo(AActor* Target);
	
	AActor* GetCurrentTarget();

	void Fire();

private:
	void OnCreated();
};
