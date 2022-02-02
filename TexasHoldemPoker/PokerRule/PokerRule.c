#include "PokerRule.h"

void InitPlayer(PLAYER* player, const wchar_t* Name, int isAI)
{
	wchar_t AINameBuffer[32];
	wchar_t Temp[32];

	static int AINumber = 0;
	
	wcscpy(AINameBuffer, L"AI_Player");

	if (isAI) // AI
	{
		wcscpy(player->Name, AINameBuffer);
		wcscat(player->Name, L" ");
		wcscat(player->Name, _itow(AINumber, Temp, 10));
		AINumber++;
	}
	else // Player
	{
		wcscpy(player->Name, Name);
	}

	player->Money = 2000;
	player->isAI = isAI;
	player->State = None_Action;
	player->BettingMoney = 0;
}

void InitPlayerMoney(PLAYER* player)
{
	player->Money = 2000;
}

void InitPlayerRoundStart(PLAYER* player)
{
	player->State = None_Action;
	player->BettingMoney = 0;
	player->PlayerRank = None_Rank;
	player->PlayerCardMaxNumber = EmptyNumber;
}

void InitPlayerTable(PLAYERTABLE* table)
{
	table->cur = 0;
	table->PlayerCount = 0;
	memset(table->players, 0, sizeof(table->players));
}

void InsertPlayerTable(PLAYERTABLE* table, PLAYER* player)
{
	int i = 0;
	if (table->PlayerCount == MAX_GAME_PLAYER_NUMBER)
		return;

	for (i = 0; i < MAX_GAME_PLAYER_NUMBER; i++)
	{
		if (table->players[i].Name == NULL)
		{
			table->players[i] = *player;
			break;
		}
	}

	table->PlayerCount++;
}

PLAYER* DeletePlayerTable(PLAYERTABLE* table, PLAYER* player)
{
	int i = 0;

	if (player == NULL)
		return NULL;

	if (table->PlayerCount == 0)
		return NULL;

	for (i = 0; i < MAX_GAME_PLAYER_NUMBER; i++)
	{
		if (!wcscmp(table->players[i].Name, player->Name))
		{
			memset((void*)&table->players[i], 0, sizeof(table->players[i]));
			break;
		}
	}
	table->PlayerCount--;

	return NULL;
}

PLAYER* CurrentPlayer(PLAYERTABLE* table)
{
	return &table->players[table->cur];
}

PLAYER* HandOverNextPlayer(PLAYERTABLE* table)
{
	if (table->PlayerCount == 0)
		return NULL;

	while (1)
	{
		table->cur++;
		table->cur = table->cur % table->PlayerCount;

		if (table->players[table->cur].Name != NULL)
			break;
	}

	return &table->players[table->cur];
}

void PrintCardNumber(enum CardNumber number)
{
	switch (number)
	{
	case Ace:
		printf("A     ");
		break;
	case Two:
		printf("2     ");
		break;
	case Three:
		printf("3     ");
		break;
	case Four:
		printf("4     ");
		break;
	case Five:
		printf("5     ");
		break;
	case Six:
		printf("6     ");
		break;
	case Seven:
		printf("7     ");
		break;
	case Eight:
		printf("8     ");
		break;
	case Nine:
		printf("9     ");
		break;
	case Ten:
		printf("10    ");
		break;
	case Jack:
		printf("Jack  ");
		break;
	case Queen:
		printf("Queen ");
		break;
	case King:
		printf("King  ");
		break;

	}
}

void PrintCardShape(enum CardShape shape)
{
	switch (shape)
	{
	case Clover:
		printf("♧");
		break;
	case Diamond:
		printf("◆");
		break;
	case Heart:
		printf("♥");
		break;
	case Spade:
		printf("♤");
		break;
	}
}

void PrintCard(CARD* cards)
{
	PrintCardShape(cards->shape);
	PrintCardNumber(cards->number);
}

void DeleteCard(CARD* cards)
{
	cards->number = EmptyNumber;
	cards->shape = EmptyShape;
}

void InitCardDeck(CARDDECK* deck)
{
	enum CardNumber cardNumber = Ace;
	enum CardShape cardShape = Clover;
	int i = 0;

	deck->top = 0;

	for (cardShape = Clover; cardShape <= Spade; ++cardShape)
	{
		for (cardNumber = Ace; cardNumber <= King; ++cardNumber)
		{
			PushCardDeck(deck, cardNumber, cardShape);
		}
	}
}

void ShakeCardDeck(CARDDECK* deck)
{
	// 알고리즘 1 : 서로 스왑할 카드를 랜덤으로 뽑고 스왑한다. 이 과정을 임의의 숫자대로 실행한다.
	int swap1;
	int swap2;
	int Count = 100;
	CARD Temp;

	printf("Shaking Cards...\n");

	while (Count >= 0)
	{
		swap1 = rand() % deck->top;
		swap2 = rand() % deck->top;

		Temp = deck->Cards[swap1];
		deck->Cards[swap1] = deck->Cards[swap2];
		deck->Cards[swap2] = Temp;

		Count--;
	}

	printf("Complete!..\n");
}

void DeleteCardDeck(CARDDECK* deck)
{
	int i = 0;
	while (1)
	{
		if (PopCardDeck(deck) == NULL)
			break;
	}

	for (i = 0; i <= MAX_CARD_NUMBER; i++)
	{
		deck->Cards[i].number = EmptyNumber;
		deck->Cards[i].shape = EmptyShape;
	}
}

void PushCardDeck(CARDDECK* deck, enum CardNumber number, enum CardShape shape)
{
	if (deck->top == MAX_CARD_NUMBER) return;
	else
	{
		deck->Cards[deck->top].number = number;
		deck->Cards[deck->top].shape = shape;
		if (deck->top + 1 < MAX_CARD_NUMBER)
			deck->top++;
	}
}

CARD* PopCardDeck(CARDDECK* deck)
{
	if (deck->top == 0) return NULL;
	else
	{
		return &deck->Cards[deck->top--];
	}
}

void GiveCard(CARDDECK* deck, PLAYER* player)
{
	player->Cards[0] = *PopCardDeck(deck);
	player->Cards[1] = *PopCardDeck(deck);
}

void CardSetToTable(CARDDECK* deck, CARD* communityCard)
{
	// 커뮤니티 카드의 숫자가 적어 하드코딩 사용
	if (communityCard[0].number == EmptyNumber)
	{
		communityCard[0] = *PopCardDeck(deck);
	}
	else if (communityCard[1].number == EmptyNumber)
	{
		communityCard[1] = *PopCardDeck(deck);
	}
	else if (communityCard[2].number == EmptyNumber)
	{
		communityCard[2] = *PopCardDeck(deck);
	}
	else if (communityCard[3].number == EmptyNumber)
	{
		communityCard[3] = *PopCardDeck(deck);
	}
	else if (communityCard[4].number == EmptyNumber)
	{
		communityCard[4] = *PopCardDeck(deck);
	}
	else
		return;
}

int BlindPhase(PLAYER* Small, PLAYER* Big)
{
	int smallDeal;
	int BigDeal;
	if (Small->isAI)
	{
		if (Small->Money < 100)
		{
			smallDeal = Small->Money;
			Small->Money = 0;
		}
		else
		{
			smallDeal = 100;
			Small->Money -= 100;
		}
	}
	else
	{
		// 플레이어 시
		printf("당신의 소지금 %d\n", Small->Money);
		while (1)
		{
			printf("얼마를 걸겠습니까? : ");
			scanf("%d", &smallDeal);
			if (smallDeal <= 0)
			{
				printf("다시 입력하세요.\n");
				continue;
			}
			else
			{
				if (smallDeal >= Small->Money)
				{
					printf("올 인\n");
					smallDeal = Small->Money;
					Small->Money = 0;
				}
				else
				{
					printf("%d 만큼 겁니다.\n", smallDeal);
					Small->Money -= smallDeal;
				}
			}
			break;
		}
	}
	Small->BettingMoney = smallDeal;

	if (Big->Money < 2 * smallDeal)
	{
		printf("빅은 자동으로 %d만큼 올인을 합니다.\n", Big->Money);
		Big->BettingMoney = Big->Money;
		Big->Money = 0;
		BigDeal = Big->BettingMoney;
	}
	else
	{
		printf("빅은 스몰의 두 배인 %d를 겁니다.\n", 2 * smallDeal);
		BigDeal = 2 * smallDeal;
		Big->Money -= BigDeal;
		Big->BettingMoney = BigDeal;
	}

	return smallDeal + BigDeal;
}


int SelectAction(PLAYER* player, int BettingMoney, int* BeforeBettingMoney)
{
	enum PlayerAction action;
	int RaiseMoney = 0;
	int inputAction = 0;

	if (player->State == Fold)
		return RaiseMoney;

	if (player->isAI)
	{
		// 임시 ai 랜덤하게 액션을 한다.
		// 나중에 인공지능을 장착한다.
		inputAction = AISelectAction(player);
	}
	else
	{
		PrintCard(&player->Cards[0]);
		PrintCard(&player->Cards[1]);
		printf("\n당신의 소지금 : %d $\n", player->Money);
		printf("\nFold[1], Call[2], Raise[3] : ");
		scanf("%d", &inputAction);
		while (!(inputAction >= 1 && inputAction <= 3))
		{
			printf("다시 입력하세요 : ");
			scanf("%d", &inputAction);
		}
	}

	switch (inputAction)
	{
	case 1: // Fold
		printf("%s가 Fold를 선택했습니다.\n", player->Name);
		action = Fold;
		player->State = Fold;
		break;
	case 2: // Call
		printf("%s가 Call을 선택했습니다.\n", player->Name);
		action = Call;
		player->State = Call;
		if (player->Money > 0) 
		{
			if (player->Money < *BeforeBettingMoney)
			{
				printf("%s는 올인을 선택했습니다.\n", player->Name);
				RaiseMoney += player->Money;
				player->BettingMoney += player->Money;
				player->Money = 0;
			}
			else
			{
				RaiseMoney += *BeforeBettingMoney;
				player->BettingMoney += *BeforeBettingMoney;
				player->Money -= *BeforeBettingMoney;
			}
		}
		else // 올인 상태
		{
			printf("%s는 올인 입니다.\n", player->Name);
		}
		break;
	case 3: // Raise
		if (player->Money <= 0)
		{
			printf("%s는 올인 입니다.\n", player->Name);
			action = Call;
			player->State = Call;
		}
		else if (player->Money <= *BeforeBettingMoney) // 베팅이 더 많은 경우 그냥 콜 처리함.
		{
			printf("플레이어 %s의 자본금이 베팅 금액과 같거나 적기 때문에 자동으로 올인 처리합니다.\n", player->Name);

			RaiseMoney += player->Money;
			player->BettingMoney += player->Money;
			player->Money = 0;

			action = Call;
			player->State = Call;
		}
		else
		{
			printf("%s가 Raise를 선택했습니다.\n", player->Name);
			action = Raise;
			player->State = Raise;
			if (player->isAI)
			{
				RaiseMoney = AIRaiseAction(player, *BeforeBettingMoney);
			}
			else
			{
				while (1)
				{
					printf("Raise할 금액을 입력하세요 : ");
					scanf("%d", &RaiseMoney);
					if (RaiseMoney > 0 && (player->Money > RaiseMoney + *BeforeBettingMoney))
					{
						RaiseMoney += *BeforeBettingMoney;
						player->Money -= RaiseMoney;
						player->BettingMoney += RaiseMoney;
						break;
					}
				}
			}
		}
		break;
	}

	return RaiseMoney;
}

int SelectFold(PLAYER* player)
{
	return 0;
}

int SelectCall(PLAYER* player)
{
	return 0;
}

int SelectRaise(PLAYER* player)
{
	return 0;
}

enum RankOfHands WhatRanks(PLAYER* player, CARD* CommunityCard)
{
	CARD AllCard[7];
	CARD SelectCards[5];
	enum CardNumber MaxNumber;
	enum RankOfHands ResultRank;
	int i = 0;
	int j = 0;
	int k = 0;
	int SelectCardsIndex = 0;
	for (i = 0; i < 2; i++)
		AllCard[i] = player->Cards[i];

	for (i = 2; i < 7; i++)
		AllCard[i] = CommunityCard[i - 2];

	// 카드를 우선 정렬한다.
	SortCard(AllCard, 7);

	for (i = 0; i < 6; i++)
	{
		for (j = i + 1; j < 7; j++)
		{
			SelectCardsIndex = 0;
			for (k = 0; k < 7; k++)
			{
				if (k == i || k == j)
					continue;
				else
				{
					SelectCards[SelectCardsIndex] = AllCard[k];
					SelectCardsIndex++;
				}
			}
			ResultRank = GetRanks(player, SelectCards, &MaxNumber);
			if (player->PlayerRank < ResultRank)
			{
				player->PlayerRank = ResultRank;
				player->PlayerCardMaxNumber = MaxNumber;
			}
			else if (player->PlayerRank == ResultRank)
			{
				if (player->PlayerCardMaxNumber < MaxNumber)
					player->PlayerCardMaxNumber = MaxNumber;
			}
		}
	}

	return ResultRank;
}

enum RankOfHands GetRanks(PLAYER* player, CARD* SelectCards, enum CardNumber *HighNumber)
{
	int i = 0;

	if (IsStraightFlush(player, SelectCards, HighNumber) == StraightFlush)
		return StraightFlush;
	else if (IsFourOfKind(player, SelectCards, HighNumber) == FourOfKind)
		return FourOfKind;
	else if (IsFullHouse(player, SelectCards, HighNumber) == FullHouse)
		return FullHouse;
	else if (IsFlush(player, SelectCards, HighNumber) == Flush)
		return Flush;
	else if (IsStraight(player, SelectCards, HighNumber) == Straight)
		return Straight;
	else if (IsThreeOfKind(player, SelectCards, HighNumber) == ThreeOfKind)
		return ThreeOfKind;
	else if (IsTwoPair(player, SelectCards, HighNumber) == TwoPair)
		return TwoPair;
	else if (IsOnePair(player, SelectCards, HighNumber) == OnePair)
		return OnePair;
	else
	{
		*HighNumber = SelectCards[4].number;
		return HighCard;
	}
}

enum RankOfHands IsOnePair(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	int j = 0;
	int PairCount = 0;
	int Count = 0;
	enum CardNumber CurrentNumber;

	for (i = 0; i < 5; i++)
	{
		CurrentNumber = CommunityCard[i].number;
		Count = 0;
		for (j = i + 1; j < 5; j++)
		{
			if (CurrentNumber == CommunityCard[j].number)
			{
				Count++;
			}
		}
		if (Count == 1)
		{
			*HighNumber = CurrentNumber;
			return OnePair;
		}
	}

	return None_Rank;
}

enum RankOfHands IsTwoPair(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	int j = 0;
	int PairCount = 0;
	int Count = 0;
	enum CardNumber CurrentNumber;
	enum CardNumber MaxNumber = EmptyNumber;

	for (i = 0; i < 5; i++)
	{
		CurrentNumber = CommunityCard[i].number;
		Count = 0;
		for (j = i + 1; j < 5; j++)
		{
			if (CurrentNumber == CommunityCard[j].number)
			{
				Count++;
			}
		}
		if (Count == 1)
		{
			PairCount++;
			if (MaxNumber < CurrentNumber)
			{
				MaxNumber = CurrentNumber;
			}
		}
	}

	if (PairCount == 2)
	{
		*HighNumber = MaxNumber;
		return TwoPair;
	}

	return None_Rank;


}

enum RankOfHands IsThreeOfKind(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	// 카드 숫자가 3개인지 확인한다.
	int i = 0;
	int j = 0;
	int Count = 0;
	enum CardNumber TripleCardNumber;

	for (i = 0; i < 3; i++)
	{
		Count = 0;
		for (j = i + 1; j < 5; j++)
		{
			if (CommunityCard[i].number == CommunityCard[j].number)
			{
				TripleCardNumber = CommunityCard[i].number;
				Count++;
			}
		}
		if (Count == 2)
		{
			*HighNumber = TripleCardNumber;
			return ThreeOfKind;
		}
	}

	return None_Rank;
}

enum RankOfHands IsStraight(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	int IsRoyalStraight = 0;

	for (i = 1; i < 5; i++)
	{
		if (CommunityCard[i - 1].number == Ace) // A 10 J Q K(로얄 스트레이트)
		{
			if (CommunityCard[i].number == Ten)
			{
				i++;
				IsRoyalStraight++;
				continue;
			}
		}

		if (CommunityCard[i - 1].number + 1 != CommunityCard[i].number)
		{
			return None_Rank;
		}
	}

	if (IsRoyalStraight)
	{
		*HighNumber = Ace;
	}
	else
	{
		*HighNumber = CommunityCard[4].number;
	}

	return Straight;
}

enum RankOfHands IsFlush(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	
	for (i = 0; i < 4; i++)
	{
		if (CommunityCard[i].shape != CommunityCard[i + 1].shape)
			return None_Rank;
	}

	*HighNumber = CommunityCard[4].number;
	return Flush;
}

enum RankOfHands IsFullHouse(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	int j = 0;
	int PairCount = 0;
	int TripleCount = 0;
	int Count = 0;
	enum CardNumber CurrentNumber;
	enum CardNumber MaxNumber = EmptyNumber;
	enum CardNumber BeforeNumber = EmptyNumber;

	for (i = 0; i < 5; i++)
	{
		CurrentNumber = CommunityCard[i].number;
		if (BeforeNumber == CurrentNumber)
			continue;
		Count = 0;
		for (j = i + 1; j < 5; j++)
		{
			if (CurrentNumber == CommunityCard[j].number)
			{
				Count++;
			}
		}
		if (Count == 2)
		{
			PairCount++;
			if (MaxNumber < CurrentNumber)
			{
				MaxNumber = CurrentNumber;
			}
		}

		if (Count == 3)
		{
			TripleCount++;
			if (MaxNumber < CurrentNumber)
			{
				MaxNumber = CurrentNumber;
			}
		}

		BeforeNumber = CurrentNumber;
	}

	if (PairCount == 1 && TripleCount == 1)
	{
		*HighNumber = MaxNumber;
		return FullHouse;
	}

	return None_Rank;
}

enum RankOfHands IsFourOfKind(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	// 카드 숫자가 4개인지 확인한다.
	int i = 0;
	int j = 0;
	int Count = 0;
	enum CardNumber number;
	for (i = 0; i < 2; i++)
	{
		Count = 0;
		for (j = i + 1; j < 5; j++)
		{
			if (CommunityCard[i].number == CommunityCard[j].number)
			{
				number = CommunityCard[i].number;
				Count++;
			}
		}
		if (Count == 4)
		{
			*HighNumber = number;
			return FourOfKind;
		}
	}

	return None_Rank;
}

enum RankOfHands IsStraightFlush(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber)
{
	int i = 0;
	int IsRoyalStraightFlush = 0;

	for (i = 1; i < 5; i++)
	{
		if (CommunityCard[i - 1].number == Ace) // A 10 J Q K(로티플)
		{
			if (CommunityCard[i].number == Ten && CommunityCard[i - 1].shape == CommunityCard[i].shape)
			{
				i++;
				IsRoyalStraightFlush++;
				continue;
			}
		}
		
		if (CommunityCard[i - 1].number + 1 != CommunityCard[i].number || CommunityCard[i - 1].shape != CommunityCard[i].shape)
		{
			return None_Rank;
		}
	}

	if (IsRoyalStraightFlush)
	{
		*HighNumber = Ace;
	}
	else
	{
		*HighNumber = CommunityCard[4].number;
	}

	return StraightFlush;
}

void SortCard(CARD* cards, int count)
{
	CARD TempCard;
	int i = 0;
	int j = 0;

	for (i = 0; i < count; i++)
	{
		for (j = i; j < count; j++)
		{
			if (cards[i].number > cards[j].number)
			{
				TempCard = cards[i];
				cards[i] = cards[j];
				cards[j] = TempCard;
			}
		}
	}
}

void PrintRank(enum RankOfHands Rank)
{
	switch (Rank)
	{
	case StraightFlush:
		printf("스트레이트 플러쉬\n"); break;
	case FourOfKind:
		printf("포카드\n"); break;
	case FullHouse:
		printf("풀하우스\n"); break;
	case Flush:
		printf("플러쉬\n"); break;
	case Straight:
		printf("스트레이트\n"); break;
	case ThreeOfKind:
		printf("트리플\n"); break;
	case TwoPair:
		printf("투페어\n"); break;
	case OnePair:
		printf("원페어\n"); break;
	case HighCard:
		printf("하이카드\n"); break;
	default:
		printf("버그발생\n"); break;
	}
}