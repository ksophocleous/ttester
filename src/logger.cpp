#include "ttester/logger.h"

#include <iostream>

namespace ttester
{
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
			std::ostream& cc = (m_logtype == type::error) ? std::cerr : std::cout;
			cc << "[" << m_logtype << "]: " << ss.str() << std::endl;
		}
	}
};