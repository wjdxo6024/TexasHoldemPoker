#pragma once

#define _MOVE_CARD 0
#define _ROTATE_CARD 1

// 뒤집는 효과는 나중에 만들기로 함.

class CardAnimation
{
private:
	float m_origPosX;
	float m_origPosY;

	float m_curPosX;
	float m_curPosY;

	float m_destinationPosX;
	float m_destinationPosY;

	float speed;

	bool m_MoveAnimation;

	int m_origWidth;
	int m_origHeight;

	int m_curWidth;
	int m_curHeight;

	bool m_RotateAnimation;
public:
	CardAnimation();
	CardAnimation(const CardAnimation& other);
	virtual ~CardAnimation();

	bool Initialize();
	bool Update(double deltaTime);
	
	bool StartRotate();

	bool StartMove(int startX, int startY, int endX, int endY, float speed = 1.0f);
	bool GetPos(int& x, int& y);
};

