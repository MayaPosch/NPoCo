/*
	Debugger.cpp - 
*/


#include "Debugger.h"
#include <sstream>
#include <cstdlib>
#include <cstdio>
#if defined(POCO_OS_FAMILY_WINDOWS)
	#include "platforms/UnWindows.h"
#elif defined(POCO_OS_FAMILY_UNIX) && !defined(POCO_VXWORKS)
	#include <unistd.h>
	#include <signal.h>
#endif
#include "UnicodeConverter.h"


// NOTE: In this module, we use the C library functions (fputs) for,
// output since, at the time we're called, the C++ iostream objects std::cout, etc.
// might not have been initialized yet.

namespace Poco {

bool Debugger::isAvailable() {
#if defined(_DEBUG)
	#if defined(POCO_OS_FAMILY_WINDOWS)
		#if defined(_WIN32_WCE)
			#if (_WIN32_WCE >= 0x600)
				BOOL isDebuggerPresent;
				if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebuggerPresent)) {
					return isDebuggerPresent ? true : false;
				}
				return false;
			#else
				return false;
			#endif
		#else
			return IsDebuggerPresent() ? true : false;
		#endif
	#elif defined(POCO_VXWORKS)
		return false;
	#elif defined(POCO_OS_FAMILY_UNIX)
		return std::getenv("POCO_ENABLE_DEBUGGER") ? true : false;
	#endif
#else
	return false;
#endif
}


void Debugger::message(const std::string& msg)
{
#if defined(_DEBUG)
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	std::fputs(msg.c_str(), stderr);
	std::fputs("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n", stderr);
	#if defined(POCO_OS_FAMILY_WINDOWS)
	if (isAvailable()) {
		std::wstring umsg;
		UnicodeConverter::toUTF16(msg, umsg);
		umsg += '\n';
		OutputDebugStringW(umsg.c_str());
	}
	#endif
#endif
}


void Debugger::message(const std::string& msg, const char* file, int line) {
#if defined(_DEBUG)
	std::ostringstream str;
	str << msg << " [in file \"" << file << "\", line " << line << "]";
	message(str.str());
#endif
}


void Debugger::enter() {
#if defined(_DEBUG)
	#if defined(POCO_OS_FAMILY_WINDOWS)
	if (isAvailable()) 	{
		DebugBreak();
	}
	#elif defined(POCO_VXWORKS) 
	{
		// not supported
	}
	#elif defined(POCO_OS_FAMILY_UNIX)
	if (isAvailable()) {
		kill(getpid(), SIGINT);
	}
	#endif
#endif
}


void Debugger::enter(const std::string& msg) {
#if defined(_DEBUG)
	message(msg);
	enter();
#endif
}


void Debugger::enter(const std::string& msg, const char* file, int line) {
#if defined(_DEBUG)
	message(msg, file, line);
	enter();
#endif
}


void Debugger::enter(const char* file, int line) {
#if defined(_DEBUG)
	message("BREAK", file, line);
	enter();
#endif
}

} // namespace Poco
