#pragma once
#include <Windows.h>
#include <Tlhelp32.h>

#include <string>

void printError(std::wstring str);

bool FindProcessW(std::wstring strApp);

/*发送模拟关闭，非强制关闭*/
bool KillProcessW(std::wstring strApp);

/*发送模拟关闭，强制关闭*/
bool TerminateApp(std::wstring strApp);
