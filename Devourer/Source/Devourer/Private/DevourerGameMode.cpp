// Copyright 2018 GitHub BlindGazer, All Rights Reserved.

#include "DevourerGameMode.h"
#include "Snake.h"

ADevourerGameMode::ADevourerGameMode()
{
    DefaultPawnClass = ASnake::StaticClass();
}
