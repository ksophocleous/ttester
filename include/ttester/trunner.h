#pragma once

#include <cstdint>
#include <typeinfo>

#include "ttester/tsuite_exception.h"

namespace ttester
{
	template<typename T>
	class trunner
	{
		public:
			uint32_t RunTests()
			{
				try
				{
					T tstsuite;
					successout() << "Test suite '" << tstsuite.GetDesc() << "' -- Running";
					successout() << "========================================";
				
					tstsuite.RunTests();

					successout() << "========================================";

					std::ostringstream ss;
					ss << "Test suite '" << tstsuite.GetDesc() << "' -- Done " << tstsuite.GetTotalTests() << " with " << tstsuite.GetFailedTestCount() << " failed";
					if (tstsuite.GetFailedTestCount() > 0)
						errorout() << ss.str();
					else
						successout() << ss.str();

					successout() << "";

					return tstsuite.GetFailedTestCount();
				}
				catch (tsuite_exception e)
				{
					errorout() << "Test runner caught tsuite_exception while running tests for " << typeid(T).name() << ": " << e.what();
					errorout() << "..this is likely due to an internal error";
				}
				catch (std::exception e)
				{
					errorout() << "std::exception while constructing test suite " << typeid(T).name() << ": " << e.what();
				}
				catch (...)
				{
					errorout() << "Unexpected exception while constructing test suite " << typeid(T).name();
				}

				// at least 1 test failed if we came here - 0 means all good
				return 1;
			}
	};
};