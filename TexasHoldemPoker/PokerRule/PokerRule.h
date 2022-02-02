#pragma once

#include "PokerDefine.h"
#include "GameAI.h"
#include <stdio.h>
#include <stdlib.h>

void InitPlayer(PLAYER* player, const wchar_t* Name, int isAI);
void InitPlayerMoney(PLAYER* player);
void InitPlayerRoundStart(PLAYER* player);

// PlayerTable ---------------------------------------------------
void InitPlayerTable(PLAYERTABLE* table);
void InsertPlayerTable(PLAYERTABLE* table, PLAYER* player);
PLAYER* DeletePlayerTable(PLAYERTABLE* table, PLAYER* player);
PLAYER* CurrentPlayer(PLAYERTABLE* table);
PLAYER* HandOverNextPlayer(PLAYERTABLE* table);
//----------------------------------------------------------------

void PrintCardNumber(enum CardNumber number);
void PrintCardShape(enum CardShape shape);
void PrintCard(CARD* cards);
void DeleteCard(CARD* cards); // Ä«µå Empty

void InitCardDeck(CARDDECK* deck);
void ShakeCardDeck(CARDDECK* deck);
void DeleteCardDeck(CARDDECK* deck);
void PushCardDeck(CARDDECK* deck, enum CardNumber number, enum CardShape shape);
CARD* PopCardDeck(CARDDECK* deck);

void GiveCard(CARDDECK* deck, PLAYER* player);
void CardSetToTable(CARDDECK* deck, CARD* communityCard);

int BlindPhase(PLAYER* Small, PLAYER* Big);

int SelectAction(PLAYER* player, int BettingMoney, int* BeforeBettingMoney);
int SelectFold(PLAYER* player);
int SelectCall(PLAYER* player);
int SelectRaise(PLAYER* player);

void SortCard(CARD* cards, int count);
enum RankOfHands GetRanks(PLAYER* player, CARD* SelectCards, enum CardNumber *HighNumber);
enum RankOfHands IsOnePair(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsTwoPair(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsThreeOfKind(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsStraight(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsFlush(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsFullHouse(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsFourOfKind(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);
enum RankOfHands IsStraightFlush(PLAYER* player, CARD* CommunityCard, enum CardNumber *HighNumber);

enum RankOfHands WhatRanks(PLAYER* player, CARD* CommunityCard);

void PrintRank(enum RankOfHands Rank);
