#include "ttester/ttester.h"
#include "ttester/core.h"
#include "ttester/tsuite.h"
#include "ttester/tsuite_exception.h"
#include "ttester/logger.h"

namespace ttester
{
	ttester::ttester() : m_failedSuites(0), m_succeededSuites(0)
	{

	}

	int ttester::Return()
	{
		if (m_failedSuites > 0)
		{
			errorout() << "Run " << (m_failedSuites + m_succeededSuites) << " test suites and got " << m_failedSuites << " that failed at least 1 test";
			return -1;
		}
		else
		{
			successout() << "All " << m_succeededSuites << " test suite(s) passed successfully";
			return 0;
		}
	}
};