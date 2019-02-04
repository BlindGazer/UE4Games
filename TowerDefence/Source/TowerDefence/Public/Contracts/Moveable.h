// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "UObject/Interface.h"
#include "Moveable.generated.h"

class AActor;

UINTERFACE(Blueprintable, MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UMoveable: public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENCE_API IMoveable
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = Navigation)
    virtual void MoveToActor(AActor* Actor) = 0;
};
