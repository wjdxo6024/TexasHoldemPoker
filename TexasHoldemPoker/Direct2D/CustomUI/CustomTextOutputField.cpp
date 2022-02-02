#include "CustomTextOutputField.h"

void CustomTextOutputField::Change()
{
	m_Counter.Change();
}

bool CustomTextOutputField::IsChange()
{
	return m_Counter.IsChange();
}