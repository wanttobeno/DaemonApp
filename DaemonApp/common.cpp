#include "common.h"
#include <Windows.h>



std::string UnicodeToAnsi(const std::wstring & wstr)
{
	// Ԥ��-�������ж��ֽڵĳ���  
	int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	// ��ָ�򻺳�����ָ����������ڴ�  
	char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
	// ��ʼ�򻺳���ת���ֽ�  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
	std::string ret_str = pAssii;
	free(pAssii);
	return ret_str;
}

std::string GetTimeA()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char szTime[30] = { 0 };
	sprintf_s(szTime, "%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return std::string(szTime);
}

std::wstring GetTimeW()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	wchar_t szTime[60] = { 0 };
	swprintf_s(szTime, L"%02d:%02d:%02d.%03d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return std::wstring(szTime);
}

