#pragma once

// UI �����̶� ���� ��� UI�� Ŀ���� Ŭ������ ��, Ŭ���� �ߴ��� ���ߴ��� �����ϴ� Ŭ�����̴�.
// UIArea�� ���� ������� �θ� Ŭ�����̴�.
class UIArea
{
public:
	virtual bool IsInside(int x, int y) = 0;
};

