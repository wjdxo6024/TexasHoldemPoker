#pragma once

enum GamePhase
{
	Blind_Phase, // ����ε� ������
	Give_Card_To_Player, // �÷��̾�� ī�带 �ش�.
	Fold_Phase, // ���� ������
	Turn_Phase, // �� ������
	River_Phase,
	Player_Action, // �� �÷��̾� ���� �׼��� ���Ѵ�.
	Round_Result
};