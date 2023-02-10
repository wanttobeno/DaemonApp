#include "SimpleFileLog.h"
#include <direct.h>
#include <time.h>
using namespace std;
#pragma warning(disable:4996)

CSimpleFileLog::CSimpleFileLog()
{

}

CSimpleFileLog* CSimpleFileLog::GetIns()
{
	static CSimpleFileLog filelog;
	return &filelog;
}

CSimpleFileLog::~CSimpleFileLog()
{
	if (m_fs.is_open())
		m_fs.close();
}

void CSimpleFileLog::InitLogFile(std::string strLogPreFix)
{
	_mkdir(".\\log");//Éú³ÉÄ¿Â¼
	time_t lt = time(NULL);
	char day[64] = { 0 };
	strftime(day, sizeof(day), "%Y-%m-%d", localtime(&lt));

	std::string strFileName(".\\log\\");
	strFileName.append(strLogPreFix);
	strFileName.append(day);
	strFileName.append(".txt");
	if (m_fs.is_open())
		m_fs.close();
	m_fs.open(strFileName, ios::app);
}

void CSimpleFileLog::log(const char* pData)
{
	if (m_fs.is_open() == false)
		return;
	m_fs << GetTime() << " " << pData << std::endl;
}

void CSimpleFileLog::log(std::string &str)
{
	if (m_fs.is_open() == false)
		return;
	m_fs << GetTime() << " " << str << std::endl;
}

std::string CSimpleFileLog::GetTime()
{
	time_t lt = time(NULL);
	char day[32];
	strftime(day, sizeof(day), "%H:%M:%S", localtime(&lt));
	return std::string(day);
}