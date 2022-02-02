#include "ChangeCounter.h"

ChangeCounter::ChangeCounter()
{
	m_ChangeCount = 0;
	m_IsChange = false;
}

ChangeCounter::~ChangeCounter()
{

}

void ChangeCounter::Change()
{
	m_ChangeCount++;

	m_IsChange = true;
}

bool ChangeCounter::IsChange()
{
	bool TmpChange;
	TmpChange = m_IsChange;
	m_ChangeCount--;

	if (m_ChangeCount > 0)
		m_IsChange = true;
	else
		m_IsChange = false;

	return TmpChange;
}