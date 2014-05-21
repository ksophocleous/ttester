#pragma once

#include <functional>
#include <sstream>

namespace ttester
{
	class logger
	{
		public:
			enum class type
			{
				success,
				info,
				warning,
				error,
			};

			typedef std::function<void(type logtype, std::string msg)> LogOutputCallback;

			logger(type logtype);
			~logger();

			template<typename T>
			friend logger&& operator<< (logger&& out, const T& value)
			{
				out.ss << value;
				return std::move(out);
			}

			static LogOutputCallback OnLogPrint;

		protected:
			std::ostringstream ss;
			type m_logtype;
	};

	std::ostream& operator<< (std::ostream& out, logger::type logtype);

	inline std::ostream& operator<< (std::ostream& out, const std::exception& exception)
	{
		out << exception.what();
		return out;
	}

	class successout : public logger
	{
		public:
			successout() : logger(logger::type::success) { }
	};

	class errorout : public logger
	{
		public:
			errorout() : logger(logger::type::error) { }
	};

	class warnout : public logger
	{
		public:
			warnout() : logger(logger::type::warning) { }
	};

	class infoout : public logger
	{
		public:
			infoout() : logger(logger::type::info) { }
	};
};