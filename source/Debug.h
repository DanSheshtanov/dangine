#pragma once

#include <string>

#if _DEBUG
#define LOG(msg) \
	OutputDebugStringA((std::string(__FILE__) + "(" + std::to_string(__LINE__) \
		+ "): " + std::string(msg) + "\n").c_str())
#else
#define UE_LOG(s)
#endif // _DEBUG