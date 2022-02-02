#include "SupportWindow.h"

SupportWindow::SupportWindow()
{

}

SupportWindow::SupportWindow(int width, int height)
{
	SupportWindowSize.push_back(std::make_pair<int, int>(1024, 768));
	SupportWindowSize.push_back(std::make_pair<int, int>(1280, 720));
	SupportWindowSize.push_back(std::make_pair<int, int>(1366, 768));
	SupportWindowSize.push_back(std::make_pair<int, int>(1600, 900));
	SupportWindowSize.push_back(std::make_pair<int, int>(1920, 1080));

	SupportWindowSizeVectorIndex = std::find(SupportWindowSize.begin(), SupportWindowSize.end(),
		std::pair<int, int>(width, height)) - SupportWindowSize.begin();
}

SupportWindow::~SupportWindow()
{

}

void SupportWindow::Initialize(int width, int height)
{
	SupportWindowSizeVectorIndex = std::find(SupportWindowSize.begin(), SupportWindowSize.end(),
		std::pair<int, int>(width, height)) - SupportWindowSize.begin();
}

std::pair<int, int> SupportWindow::NextScreen()
{
	if (SupportWindowSizeVectorIndex >= SupportWindowSize.size() - 1)
		SupportWindowSizeVectorIndex = SupportWindowSize.size() - 1;
	else
		SupportWindowSizeVectorIndex++;
	return SupportWindowSize[SupportWindowSizeVectorIndex];
}

std::pair<int, int> SupportWindow::CurrentScreen()
{
	return SupportWindowSize[SupportWindowSizeVectorIndex];
}

std::pair<int, int> SupportWindow::PrevScreen()
{
	SupportWindowSizeVectorIndex--;
	if (SupportWindowSizeVectorIndex < 0)
		SupportWindowSizeVectorIndex = 0;

	return SupportWindowSize[SupportWindowSizeVectorIndex];
}