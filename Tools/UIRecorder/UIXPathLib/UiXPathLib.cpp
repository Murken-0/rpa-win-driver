#include "stdafx.h"
#include <windows.h>
#include "UiTreeWalk.h"

HookProc UserMouseHookCallback = nullptr;
HookProc UserKeyboardHookCallback = nullptr;
HHOOK hookMouse = nullptr;
HHOOK hookKeyboard = nullptr;

static LRESULT CALLBACK InternalMouseHookCallback(int code, WPARAM wparam, LPARAM lparam)
{
    if (code < 0)
    {
        return CallNextHookEx(hookMouse, code, wparam, lparam);
    }

    if (UserMouseHookCallback != nullptr)
    {
        UserMouseHookCallback(code, wparam, lparam);
    }

    return CallNextHookEx(hookMouse, code, wparam, lparam);
}

static LRESULT CALLBACK InternalKeyboardHookCallback(int code, WPARAM wparam, LPARAM lparam)
{
    if (code < 0)
    {
        return CallNextHookEx(hookKeyboard, code, wparam, lparam);
    }

    if (UserKeyboardHookCallback != nullptr)
    {
        UserKeyboardHookCallback(code, wparam, lparam);
    }

    return CallNextHookEx(hookKeyboard, code, wparam, lparam);
}

extern "C" HHOOK __declspec(dllexport) WINAPI SetWindowsHookExNative(HookProc userProc, UINT hookID, UINT uThreadId)
{
    if (hookID == WH_MOUSE_LL)
    {
        UserMouseHookCallback = userProc;
        hookMouse = SetWindowsHookEx(WH_MOUSE_LL, static_cast<HOOKPROC>(InternalMouseHookCallback), g_hModule, 0);
        return hookMouse;
    }
    else if (hookID == WH_KEYBOARD_LL)
    {
        UserKeyboardHookCallback = userProc;
        hookKeyboard = SetWindowsHookEx(WH_KEYBOARD_LL, static_cast<HOOKPROC>(InternalKeyboardHookCallback), g_hModule, 0);
        return hookKeyboard;
    }
    else
    {
        return nullptr;
    }
}

extern "C" void __declspec(dllexport) WINAPI UninitializeHook(HHOOK hHook)
{
    UnhookWindowsHookEx(hHook);
}

extern "C" void __declspec (dllexport) WINAPI InitUiTreeWalk()
{
    UiTreeWalk::Init();
}

extern "C"  void __declspec (dllexport) WINAPI UnInitUiTreeWalk()
{
    UiTreeWalk::UnInit();
}

BOOL IsPointOnOwnHwnd(_In_ long left, _In_ long top)
{
    POINT pt{ left, top };

    HWND hwnd = WindowFromPhysicalPoint(pt);
    DWORD dwProcId = 0;
    GetWindowThreadProcessId(hwnd, &dwProcId);

    DWORD dwThisProcId = GetCurrentProcessId();
    if (dwProcId == dwThisProcId)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

extern "C"  long __declspec (dllexport) WINAPI GetUiXPath(_In_ long left, _In_ long top, _Out_writes_to_(nMaxCount, return) LPWSTR lpUiPath, _In_ int nMaxCount)
{
    if (IsPointOnOwnHwnd(left, top) == TRUE)
    {
        return 0;
    }

    return UiTreeWalk::GetUiXPath(left, top, lpUiPath, nMaxCount);
}

extern "C" ULONG __declspec (dllexport) WINAPI HighlightCachedUI(_In_ LPWSTR lpRumtimeId, _Out_ RECT *pRect)
{
    return UiTreeWalk::HighlightCachedUI(lpRumtimeId, pRect);
}
