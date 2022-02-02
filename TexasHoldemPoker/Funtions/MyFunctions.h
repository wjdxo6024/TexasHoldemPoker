#pragma once
#include <cstdio>
#include <string>
#include <cstring>
#include <atlstr.h>

#define SAFE_RELEASE(x) if(x != NULL) {x->Release(); x = 0;}
#define SAFE_RELEASE_AND_DELETE(x) if(x != NULL) {x->Release(); delete x; x = 0;}
#define SAFE_DELETE(x) if(x != NULL) {delete x; x = 0;}
#define SAFE_DELETE_ARRAY(x) if(x != NULL) {delete [] x; x = 0;}

// find the file size
namespace MyFunctions {
	int GetFileSize(FILE* inFile);

	std::wstring StringToWstring(const std::string& _src);
	std::string WstringToString(const std::wstring& _src);

	int ScalingUI_X(int x, int currentWindowWidth);
	int ScalingUI_Y(int y, int currentWindowHeight);
	int ScalingUI_Font(int org_font, int windowWidth, int windowHeight);
}
