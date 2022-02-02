#pragma once
#ifndef _GAMEAI_H_
#define _GAMEAI_H_
#include "PokerDefine.h"

enum PlayerAction AISelectAction(PLAYER *player);
int AIRaiseAction(PLAYER *player, int BettingMoney);

#endif