#include "ttester/core.h"

#ifdef _WIN32
# include <windows.h>
#endif

void breakdebugger()
{
#ifdef _WIN32
	if (IsDebuggerPresent() == TRUE)
		DebugBreak();
#endif
}