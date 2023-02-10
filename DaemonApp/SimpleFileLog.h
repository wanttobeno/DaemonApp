#pragma once

#include <fstream>
#include <string>

class CSimpleFileLog
{
public:
	static CSimpleFileLog* GetIns();

	virtual ~CSimpleFileLog();

	void InitLogFile(std::string strLogPreFix);

	void log(const char* pData);
	void log(std::string &str);
protected:
	CSimpleFileLog();
	std::string GetTime();

protected:
	std::fstream m_fs;
};

