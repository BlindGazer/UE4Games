// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "BaseProjectile.h"
#include "TowerDefence.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "UObject/ConstructorHelpers.h"

ABaseProjectile::ABaseProjectile()
{
    bInitialized = false;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->InitSphereRadius(10);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
    Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
    Collision->SetCanEverAffectNavigation(false);
	Collision->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);

    RootComponent = Collision;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Mesh->AttachToComponent(Collision, FAttachmentTransformRules::KeepRelativeTransform);  
    Mesh->SetRelativeRotation(FRotator(-90, 0, 0));

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = Collision;
    ProjectileMovement->ProjectileGravityScale = 0.0f;
    ProjectileMovement->Velocity = FVector::ZeroVector;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->bRotationFollowsVelocity = false;
	InitialLifeSpan = 3.0f;
    AdditionalLifeSpan = 0.5f;
}

void ABaseProjectile::Init(const FVector& Destination, const FProjectileAttributes& Attributes)
{
	if (Attributes.Speed <= 0)
	{
		UE_LOG(LogGame, Log, TEXT("ABaseProjectile::Init InitialSpeed is invalid"));
		Destroy();

		return;
	}

	float TimeToHit = FVector::Dist(GetActorLocation(), Destination) / Attributes.Speed;

    ProjectileMovement->InitialSpeed =
        ProjectileMovement->MaxSpeed = Attributes.Speed;
    ProjectileMovement->Velocity = GetActorRotation().RotateVector(FVector(Attributes.Speed, 0, 0));
    SetLifeSpan(TimeToHit + AdditionalLifeSpan);
    bInitialized = true;
    ABaseProjectile::Attributes = Attributes;
}

void ABaseProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
        DealDamage(OtherActor);
        BP_OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
    }

    Destroy();
}

void ABaseProjectile::DealDamage(AActor* Target)
{
    if (Attributes.Damage > 0)
    {
        Target->TakeDamage(Attributes.Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
    }
}
