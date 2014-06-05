#include "ttester/tmain.h"
#include "ttester/core.h"
#include "ttester/tsuite.h"
#include "ttester/tsuite_exception.h"
#include "ttester/logger.h"

#include <cassert>
#include <cstdlib>

namespace ttester
{
	std::vector<tmain::RegFunc>* s_registerFunctions;

	tmain::tmain(int argc, char* argv[]) : m_failedSuites(0), m_succeededSuites(0)
	{
		assert(argc >= 0);

#ifndef DISABLE_TTESTER
		for (int i = 0; i < argc; i++)
		{
			
			std::string opt = argv[i];
			if (opt.compare("--test") == 0)
			{
				exit(RunAllTests());
			}
		}
#endif
	}

	int tmain::RunAllTests()
	{
		if (s_registerFunctions)
		{
			for (auto each : *s_registerFunctions)
				each(*this);
		}

		return Return();
	}

	//static 
	void tmain::RegisterTest(RegFunc regfunc)
	{
		if (s_registerFunctions == nullptr)
			s_registerFunctions = new std::vector<tmain::RegFunc>;

		s_registerFunctions->emplace_back(std::move(regfunc));
	}

	int tmain::Return()
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
