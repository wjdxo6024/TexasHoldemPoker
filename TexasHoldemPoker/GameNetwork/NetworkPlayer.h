#pragma once
#include <string>

// 네트워크 플레이는 크게 두 가지로 나뉜다. 하나는 자기가 서버(룸)을 만들거나 하나는 룸에 들어가는 것이다.
// 

class NetworkPlayer
{
private:
	std::string m_PlayerNickName;

public:
	bool SetNickName();
	std::string GetNickName();
};

