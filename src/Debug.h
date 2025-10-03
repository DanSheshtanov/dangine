#pragma once


#if _DEBUG
#include <Windows.h>
#include <string>

#define LOG(msg) \
	OutputDebugStringA((std::string(__FILE__) + "(" + std::to_string(__LINE__) \
		+ "): " + std::string(msg) + "\n").c_str())

#define LOGDIRECT(msg) \
	OutputDebugStringA((std::string(msg) + "\n").c_str());

#else
#define LOG(msg)
#define LOGDIRECT(msg)
#endif // _DEBUG