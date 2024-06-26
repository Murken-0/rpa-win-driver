// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <atlbase.h>
#include <UIAutomation.h>
#include <UIAutomationClient.h>

// TODO: reference additional headers your program requires here
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#include <map>

typedef void (CALLBACK *HookProc)(int code, WPARAM w, LPARAM l);
extern HMODULE g_hModule;

#define REQUIRE_SUCCESS_HR(hr)                                                                                                               \
    do                                                                                                                                            \
    {                                                                                                                                             \
        HRESULT __hr = (hr);                                                                                                                      \
        if (FAILED(__hr))                                                                                                                         \
        {                                                                                                                                         \
            std::cout << "hr:" << std::hex << (unsigned int)hr << ", LINE:" << __LINE__ << ", FUNC:" << __FUNCTION__;                             \
            return hr;                                                                                                                            \
        }                                                                                                                                         \
    } while (false)