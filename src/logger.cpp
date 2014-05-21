#include "ttester/logger.h"

#include <iostream>
#include <ctime>
#include <iomanip>

static std::tm* getlocaltime(std::tm* tmstruct)
{
	time_t t;
	std::time(&t);
#ifdef _WIN32
	localtime_s(tmstruct, &t);
	return tmstruct;
#else
	struct tm* tcopy = localtime(&t);
	return tcopy;
#endif
}

namespace ttester
{
	//static 
	logger::LogOutputCallback logger::OnLogPrint;

	std::ostream& operator<< (std::ostream& out, logger::type logtype)
	{
		switch (logtype)
		{
			case logger::type::success: out << "success"; return out;
			case logger::type::info: out << "info"; return out;
			case logger::type::warning: out << "warning"; return out;
			case logger::type::error: out << "error"; return out;
		}

		out << "unknown";
		return out;
	}

	logger::logger(type logtype) : m_logtype(logtype) { }

	logger::~logger()
	{
		if (OnLogPrint)
			OnLogPrint(m_logtype, ss.str());
		else
		{
			std::tm timev;
			std::tm* tcopy = getlocaltime(&timev);
			std::ostream& cc = (m_logtype == type::error) ? std::cerr : std::cout;
			cc << (tcopy->tm_year + 1900) << "-" << 
				std::setw(2) << std::setfill('0') << (tcopy->tm_mon + 1) << "-" <<
				std::setw(2) << std::setfill('0') << (tcopy->tm_mday + 1) << " " <<
				
				std::setw(2) << std::setfill('0') << (tcopy->tm_hour) << ":" <<
				std::setw(2) << std::setfill('0') << (tcopy->tm_min) << ":" <<
				std::setw(2) << std::setfill('0') << (tcopy->tm_sec) << " -- ";

			cc << "[" << m_logtype << "]: " << ss.str() << std::endl;
		}
	}
};