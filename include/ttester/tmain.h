#pragma once

#include <ttester/core.h>
#include <ttester/trunner.h>
#include <ttester/tsuite.h>
#include <ttester/tsuite_exception.h>

namespace ttester
{
	class tmain
	{
		public:
			typedef std::function<void(tmain&)> RegFunc;

			tmain(int argc, char* argv[]);

			int RunAllTests();

			static void RegisterTest(RegFunc regfunc);

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

	template<typename T>
	bool RegTestFunc()
	{
		auto func = [] (tmain& tmain)
		{
			tmain.RunTestSuite<T>();
		};

		tmain::RegisterTest(std::move(func));

		return true;
	}

#ifdef DISABLE_TTESTER
	#define REGISTER_TEST_CLASS(_CLASS)
#else
	#define REGISTER_TEST_CLASS(_CLASS) \
		static bool _reg##_CLASS = ttester::RegTestFunc<_CLASS>();
#endif
};