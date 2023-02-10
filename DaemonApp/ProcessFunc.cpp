#include "ProcessFunc.h"

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <sstream>

#ifdef _UNICODE
void printError(std::wstring str)
{
	OutputDebugString(str.c_str());
}
#else
void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf( TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}
#endif // _UNICODE

DWORD GetProcessID(std::wstring strApp)
{
	DWORD dwPId = 0;
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
		return(FALSE);
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		printError(TEXT("Process32First")); // show cause of failure
		CloseHandle(hProcessSnap);          // clean the snapshot object
		return(FALSE);
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		//_tprintf( TEXT("\n\n====================================================="));
		//_tprintf( TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);
		//_tprintf( TEXT("\n-------------------------------------------------------"));

		std::wstring::size_type nPos = strApp.find(pe32.szExeFile);
		if (nPos != std::wstring::npos)
		{
			dwPId = pe32.th32ProcessID;
			break;
		}

		// Retrieve the priority class.
		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		if (hProcess == NULL)
		{
			//printError(TEXT("OpenProcess"));
		}
		else
		{
			dwPriorityClass = GetPriorityClass(hProcess);
			if (!dwPriorityClass)
				printError(TEXT("GetPriorityClass"));
			CloseHandle(hProcess);
		}

		//_tprintf( TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
		//_tprintf( TEXT("\n  Thread count      = %d"), pe32.cntThreads);
		//_tprintf( TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID);
		//_tprintf( TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
		//if (dwPriorityClass)
		//	_tprintf( TEXT("\n  Priority class    = %d"), dwPriorityClass);

		// List the modules and threads associated with this process
		//ListProcessModules(pe32.th32ProcessID);
		//ListProcessThreads(pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	return dwPId;
}


bool FindProcessW(std::wstring strApp)
{
	bool bRet = false;
	DWORD dwPid = GetProcessID(strApp);
	if (dwPid > 0)
		return true;
	return false;
}

bool KillProcessW(std::wstring strApp)
{
	DWORD dwProcessId = GetProcessID(strApp);
	if (dwProcessId <= 0)
	{
		return false;
	}
	std::wostringstream oss;
	oss.str(_T(""));
	oss << _T("/PID ");
	oss << dwProcessId;
	std::wstring strCmd = oss.str();
	ShellExecute(NULL, _T("open"), _T("taskkill.exe"), strCmd.c_str(), _T(""), SW_HIDE);

	DWORD dError = ::GetLastError();
	if (ERROR_SUCCESS != dError)
	{
		return false;
	}
	return true;
}

bool TerminateApp(std::wstring strApp)
{
	bool bRet = false;
	DWORD dwProcessId = GetProcessID(strApp);
	if (dwProcessId <= 0)
	{
		return bRet;
	}
	HANDLE hProc = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, dwProcessId);
	if (hProc == NULL)
	{
		return bRet;
	}
	bRet =::TerminateProcess(hProc, 4);
	CloseHandle(hProc);
	return bRet;
}
