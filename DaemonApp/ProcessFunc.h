#pragma once
#include <Windows.h>
#include <Tlhelp32.h>

#include <string>

void printError(std::wstring str);

bool FindProcessW(std::wstring strApp);

/*����ģ��رգ���ǿ�ƹر�*/
bool KillProcessW(std::wstring strApp);

/*����ģ��رգ�ǿ�ƹر�*/
bool TerminateApp(std::wstring strApp);
