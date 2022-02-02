#pragma once

enum GamePhase
{
	Blind_Phase, // 블라인드 페이즈
	Give_Card_To_Player, // 플레이어에게 카드를 준다.
	Fold_Phase, // 폴드 페이즈
	Turn_Phase, // 턴 페이즈
	River_Phase,
	Player_Action, // 각 플레이어 끼리 액션을 정한다.
	Round_Result
};