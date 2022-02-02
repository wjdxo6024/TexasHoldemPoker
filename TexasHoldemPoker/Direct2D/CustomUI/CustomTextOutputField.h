#pragma once
#include "../AdvancedUI/TextOutputField.h"
#include "../../Funtions/ChangeCounter.h"
class CustomTextOutputField :
	public TextOutputField
{
private:
	ChangeCounter m_Counter;

public:
	void Change();
	bool IsChange();
};

