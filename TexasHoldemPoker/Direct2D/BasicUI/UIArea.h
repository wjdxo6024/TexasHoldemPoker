#pragma once

// UI 영역이란 예를 들어 UI에 커서가 클릭했을 때, 클릭을 했는지 않했는지 판정하는 클래스이다.
// UIArea는 각종 에어리어의 부모 클래스이다.
class UIArea
{
public:
	virtual bool IsInside(int x, int y) = 0;
};

