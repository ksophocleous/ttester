#pragma once

#include <string>
#include <stdexcept>

namespace ttester
{
	class tsuite_exception : public std::runtime_error
	{
		public:
			tsuite_exception(std::string msg) : std::runtime_error(msg.c_str()) { }
	};
};