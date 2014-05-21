#pragma once

#include <string>
#include <cstdint>
#include <functional>

#include "ttester/logger.h"

namespace ttester
{
	class tsuite
	{
		public:
			tsuite(std::string desc);
			virtual ~tsuite();

			std::string GetDesc() const { return m_desc; }

			uint32_t GetTotalTests() const { return m_failed + m_passed; }
			uint32_t GetFailedTestCount()  const { return m_failed; }
			uint32_t GetSuccessTestCount()  const { return m_passed; }

			virtual void RunTests() = 0;

		protected:
			void test(std::string name, std::function<void()> testfunc);

			template<typename T>
			void test_exception(std::string name, std::function<void()> testfunc)
			{
				std::ostringstream ss;
				ss << name;
				try
				{
					testfunc();
					m_failed++;
					errorout() << name << " -> failed because tested code did not throw an exception as expected";
				}
				catch (T e)
				{
					m_passed++;
					successout() << name/* << " -> (" << e << ")"*/;
				}
				catch (...)
				{
					m_failed++;
					errorout() << name << " -> failed because of incorrect exception caught";
				}
			}

		private:
			std::string m_desc;
			uint32_t m_passed, m_failed;
	};
};