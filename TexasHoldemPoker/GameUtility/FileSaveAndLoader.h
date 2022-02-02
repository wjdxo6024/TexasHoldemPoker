#pragma once
#include <cstdio>
#include <list>
#include "../GameOption/GameOption.h"

void AllFileLoad(GameOption* option);
void AllFileSave(GameOption* option);

void OptionLoad(FILE** fp, GameOption* option);
void OptionSave(FILE** fp, GameOption* option);

void GamePlayDataLoad(FILE** fp);
void GamePlayDataSave(FILE** fp);


