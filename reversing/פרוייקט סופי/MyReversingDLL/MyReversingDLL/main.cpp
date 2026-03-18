#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

// פונקציה שתופיע ב-IDA וב-CFF Explorer
extern "C" __declspec(dllexport)
void DecodeIRGC()
{
    MessageBoxA(NULL, "IRGC decoded!", "Mission Success", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    return TRUE;
}
