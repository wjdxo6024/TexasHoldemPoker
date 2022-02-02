#pragma once
#include <vector>

class SupportWindow
{
private:
	std::vector<std::pair<int, int>> SupportWindowSize;
	int SupportWindowSizeVectorIndex;

public:
	SupportWindow();
	SupportWindow(int width, int height);
	virtual ~SupportWindow();

	void Initialize(int width, int height);

	std::pair<int, int> NextScreen();
	std::pair<int, int> CurrentScreen();
	std::pair<int, int> PrevScreen();
};

