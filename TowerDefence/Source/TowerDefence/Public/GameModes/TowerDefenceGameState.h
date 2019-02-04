// Copyright 2019 GitHub BlindGazer, All Rights Reserved.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "TowerDefenceGameState.generated.h"

class ABaseEnemy;

UCLASS()
class TOWERDEFENCE_API ATowerDefenceGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    ATowerDefenceGameState();

    void OnEnemyDied(ABaseEnemy* Enemy);
};
