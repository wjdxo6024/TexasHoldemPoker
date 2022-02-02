// find the file size
#include "MyFunctions.h"
#include "../GameOption/GameOption.h"
namespace MyFunctions {
	int GetFileSize(FILE* inFile)
	{
		int fileSize = 0;
		int Current = ftell(inFile);
		fseek(inFile, 0, SEEK_END);

		fileSize = ftell(inFile);

		fseek(inFile, Current, SEEK_SET);
		return fileSize;
	};

	std::wstring StringToWstring(const std::string& _src)
	{
		USES_CONVERSION;
		return std::wstring(A2W(_src.c_str()));
	};

	std::string WstringToString(const std::wstring& _src)
	{
		USES_CONVERSION;
		return std::string(W2A(_src.c_str()));
	};

	int ScalingUI_X(int x, int currentWindowWidth)
	{
		return x * currentWindowWidth / STANDARDWINDOW_WIDTH;
	}

	int ScalingUI_Y(int y, int currentWindowHeight)
	{
		return y * currentWindowHeight / STANDARDWINDOW_HEIGHT;
	}

	int ScalingUI_Font(int org_font, int windowWidth, int windowHeight) // ¹Ì¿Ï¼º
	{
		return 0;
	}
}
