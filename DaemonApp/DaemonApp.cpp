// DaemonApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <tchar.h>
#include "ProcessFunc.h"
#include <Shlwapi.h>

#pragma comment(lib,"Shlwapi.lib")

#include "SimpleFileLog.h"
#include "common.h"


void DbgInfoA(std::string str)
{
	std::string strLog;
	strLog = GetTimeA();
	strLog.append(" ");
	strLog.append(str);
	OutputDebugStringA(strLog.c_str());
	CSimpleFileLog* pLog = CSimpleFileLog::GetIns();
	pLog->log(str.c_str());
}

void DbgInfoW(std::wstring str)
{
	std::string strLog = UnicodeToAnsi(str);
	DbgInfoA(strLog);
}


int main()
{
	setlocale(LC_ALL, "chs");
	bool bExist = PathFileExists(L"./Setting.ini");
	wchar_t szBuf[MAX_PATH] = { 0 };
	::GetPrivateProfileString(L"AppSetting", L"CheckAppName", L"osk.exe", szBuf, MAX_PATH, L"./Setting.ini");
	//::GetPrivateProfileString(L"AppSetting", L"CheckAppName", L"WerFault.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strCheckAppName = szBuf;

	::GetPrivateProfileString(L"AppSetting", L"RunAppName", L"notepad.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strRunAppName = szBuf;

	::GetPrivateProfileString(L"AppSetting", L"AppFullPath", L"C:\\Windows\\System32\\notepad.exe", szBuf, MAX_PATH, L"./Setting.ini");
	std::wstring strAppFullPath = szBuf;
	int nCycleTime = GetPrivateProfileIntW(L"AppSetting", L"CycleTime", 3000, L"./Setting.ini");
	if (nCycleTime < 3000)
		nCycleTime = 3000;

	CSimpleFileLog* pLog = CSimpleFileLog::GetIns();
	pLog->InitLogFile("DaemonApp-");
	pLog->log("\tStart");
	int i = 3;
	do
	{
		bool bFind1 = FindProcessW(strCheckAppName);
		bool bFind2 = FindProcessW(strRunAppName);
		if (bFind1==false && bFind2==true)
		{
			DbgInfoW(L"未发现报错进程！");
			wprintf(L"%s %s程序执行中，未发现报错\n",GetTimeW().c_str(), strRunAppName.c_str());
			Sleep(nCycleTime);
			continue;
		}
	
		if (bFind1)
		{
			DbgInfoW(L"关闭报错和卡死程序！");
			wprintf(L"%s 关闭报错和卡死程序\n", GetTimeW().c_str());
			KillProcessW(strCheckAppName);
			KillProcessW(strRunAppName);
			TerminateApp(strCheckAppName);
			TerminateApp(strRunAppName);
			continue;
		}
		if (bFind2==false)
		{
			if (PathFileExists(strAppFullPath.c_str()))
			{
				DbgInfoW(L"启动进程！");
				wprintf(L"%s 启动进程 %s\n", GetTimeW().c_str(), strAppFullPath.c_str());
				ShellExecute(NULL, _T("open"), _T("explorer.exe"), strAppFullPath.c_str(), NULL, SW_SHOWDEFAULT);
				Sleep(10000);
			}
			else
			{
				DbgInfoW(L"启动进程不存在！");
				wprintf(L"%s 启动进程不存在 %s\n", GetTimeW().c_str(), strAppFullPath.c_str());
			}
		}

		Sleep(nCycleTime);
	} while (1);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
