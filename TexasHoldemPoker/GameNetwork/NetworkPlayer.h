#pragma once
#include <string>

// ��Ʈ��ũ �÷��̴� ũ�� �� ������ ������. �ϳ��� �ڱⰡ ����(��)�� ����ų� �ϳ��� �뿡 ���� ���̴�.
// 

class NetworkPlayer
{
private:
	std::string m_PlayerNickName;

public:
	bool SetNickName();
	std::string GetNickName();
};

