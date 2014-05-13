#include "ttester/tsuite.h"
#include "ttester/tsuite_exception.h"
#include "ttester/logger.h"

namespace ttester
{
	tsuite::tsuite(std::string desc) : m_desc(std::move(desc)), m_passed(0), m_failed(0)
	{

	}

	tsuite::~tsuite()
	{

	}

	void tsuite::test(std::string name, std::function<void()> testfunc)
	{
		try
		{
			testfunc();
			m_passed++;
			successout() << name;
		}
		catch (std::exception e)
		{
			m_failed++;
			errorout() << name << " -> failed because of " << e;
	#if defined(_DEBUG) && defined(_MSC_VER)
			__debugbreak();
	#endif
		}
		catch (...)
		{
			errorout() << name << " -> failed because of uncatched (and non-std::exception based) exception";
			throw;
		}
	}
};