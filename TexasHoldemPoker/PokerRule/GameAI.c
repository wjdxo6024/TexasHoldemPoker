#include "GameAI.h"
#include <stdio.h>
#include <stdlib.h>

enum PlayerAction AISelectAction(PLAYER *player)
{
	int AISelect = 0;

	AISelect = rand() % 3 + 1;
	switch (AISelect)
	{
	case 1:
		player->State = Fold;
		break;
	case 2:
		player->State = Call;
		break;
	case 3:
		player->State = Raise;
		break;
	}

	return player->State;
}

int AIRaiseAction(PLAYER *player, int BettingMoney)
{
	int RaiseMoney = 0;
	RaiseMoney = 100;

	while (1)
	{
		if (player->Money < BettingMoney + RaiseMoney)
		{
			RaiseMoney /= 2;
		}
		else
		{
			player->Money -= BettingMoney + RaiseMoney;
			player->BettingMoney += BettingMoney + RaiseMoney;
			break;
		}

	}
	
	return BettingMoney + RaiseMoney;
}