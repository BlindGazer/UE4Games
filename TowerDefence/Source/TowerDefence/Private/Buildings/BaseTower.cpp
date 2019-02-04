// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "BaseTower.h"
#include "TowerDefence.h"
#include "BaseProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "ProjectileAttributes.h"
#include "EnemyInterface.h"

ABaseTower::ABaseTower(): 
    Super(), AttackSpeed(1.0f), 
	Damage(25), ProjectileSpeed(1000),
    CreationTime(0)
{
    AttackArea = CreateDefaultSubobject<USphereComponent>("AttackArea");
    AttackArea->InitSphereRadius(500.0f);
    AttackArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    AttackArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

    RootComponent = AttackArea;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->AttachToComponent(AttackArea, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABaseTower::BeginPlay()
{
    World = GetWorld();
	check(World)

    TimerManager = &World->GetTimerManager();
    TimerManager->SetTimer(
        AttackTimer, 
        this, &ABaseTower::OnCreated,
        (CreationTime > 0 ? CreationTime : 0.1f));

    Super::BeginPlay();
}

void ABaseTower::OnAreaEnter(AActor* Area, AActor* Actor)
{
    if (Actor && AttackSpeed > 0)
    {
        Targets.Enqueue(Actor);

        if (!bIsActive)
        {
            bIsActive = true;
            Fire();
        }
    }
}

void ABaseTower::OnCreated()
{
    OnActorBeginOverlap.AddDynamic(this, &ABaseTower::OnAreaEnter);
    BP_OnCreated();
}

bool ABaseTower::SpawnProjectile(AActor* Target) const
{
	if (!ProjectileClass)
	{
		UE_LOG(LogGame, Log, TEXT("ABaseTower::Fire ProjectileClass is empty"));
		return false;
	}

	FActorSpawnParameters ProjectileSpawnParameters;
	ProjectileSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	auto Projectile = World->SpawnActor<ABaseProjectile>(
        ProjectileClass, 
        Mesh->GetSocketTransform("Projectile"), 
        ProjectileSpawnParameters);
	
	if (Projectile)
	{
		InitProjectile(Projectile, Target);
		return true;
	}

	return false;
}

void ABaseTower::InitProjectile(ABaseProjectile* Projectile, AActor* Target) const
{
    Projectile->Init(Target->GetActorLocation(), FProjectileAttributes { Damage, DamageRadius, ProjectileSpeed });
}

void ABaseTower::PlayAnimation() const
{
	if (FireAnimation)
	{
		if (Mesh)
		{
            Mesh->PlayAnimation(FireAnimation, false);
		}
	}	
}

void ABaseTower::PlaySound() const
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void ABaseTower::RotateTo(AActor* Target)
{
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation()));
}

AActor* ABaseTower::GetCurrentTarget()
{
    if (Targets.IsEmpty())
    {
        return nullptr;
    }

    AActor* CurrentTarget;

    do
    {
        Targets.Peek(CurrentTarget);
        bool bIsValid = false;

        if (CurrentTarget)
        {
            auto Enemy = Cast<IEnemyInterface>(CurrentTarget);
            if (Enemy)
            {
                bIsValid = !Enemy->IsDead() && IsOverlappingActor(CurrentTarget);
            }
        }

        if(bIsValid)
        {
            return CurrentTarget;
        }
        else
        {
            Targets.Pop();
        }
    } while (!Targets.IsEmpty());

    return nullptr;
}

void ABaseTower::Fire()
{
	AActor* Target = GetCurrentTarget();

	if (!Target)
	{
		bIsActive = false;
		return;
	}

	RotateTo(Target);

	if (!SpawnProjectile(Target))
	{
		return;
	}

	PlayAnimation();
	PlaySound();

	TimerManager->SetTimer(AttackTimer, this, &ABaseTower::Fire, AttackSpeed);
}