// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#include "WavePoint.h"
#include "TowerDefence.h"
#include "Moveable.h"
#include "Components/DecalComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

AWavePoint::AWavePoint()
{
    const auto DefaultSize = FVector(200, 200, 200);

    PointArea = CreateDefaultSubobject<UBoxComponent>("PointArea");
    PointArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    PointArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
    PointArea->SetBoxExtent(DefaultSize);

    RootComponent = PointArea;

    Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
    Decal->SetRelativeLocation(FVector(0, 0, -DefaultSize.Z / 2));
    Decal->SetRelativeRotation(FRotator(90, 0, 0));
    Decal->AttachToComponent(PointArea, FAttachmentTransformRules::KeepRelativeTransform);
    Decal->DecalSize = DefaultSize;

    static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalFinder(TEXT("/Game/TowerDefence/Environment/MI_DestinationZone"));
    auto MaterialInstance = UMaterialInstanceDynamic::Create(DecalFinder.Object, NULL);
    Decal->SetDecalMaterial(MaterialInstance);

    OnActorBeginOverlap.AddDynamic(this, &AWavePoint::OnEnterArea);
}

void AWavePoint::OnEnterArea(AActor* Point, AActor* OtherActor)
{
    const auto MoveableActor = Cast<IMoveable>(OtherActor);

    if (MoveableActor)
    {
        if (bIsFinish)
        {
			OtherActor->Destroy();
        }
        else if (NextPoint)
        {
			MoveableActor->MoveToActor(NextPoint);
        }
    }
}
