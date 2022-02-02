#pragma once
class ChangeCounter
{
private:
	bool m_IsChange;
	int m_ChangeCount;
public:
	ChangeCounter();
	~ChangeCounter();

	void Change();
	bool IsChange();
};