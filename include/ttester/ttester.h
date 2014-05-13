#pragma once

#include <ttester/core.h>
#include <ttester/trunner.h>
#include <ttester/tsuite.h>
#include <ttester/tsuite_exception.h>

namespace ttester
{
	class ttester
	{
		public:
			ttester();

			template<typename T>
			void RunTestSuite()
			{
				trunner<T> runner;

				// returns how many failures this test suit had
				if (runner.RunTests() > 0)
					m_failedSuites++;
				else
					m_succeededSuites++;
			}

			int Return();

		private:
			uint32_t m_failedSuites;
			uint32_t m_succeededSuites;
	};
};