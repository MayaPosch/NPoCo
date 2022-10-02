/*
	Process_UNIX.h - Definition of the ProcessImpl class for Unix.
*/


#ifndef Core_Process_UNIX_INCLUDED
#define Core_Process_UNIX_INCLUDED


#include "../Core.h"
#include "../RefCountedObject.h"
#include <unistd.h>
#include <vector>
#include <map>


namespace Poco {


class Pipe;


class Foundation_API ProcessHandleImpl: public RefCountedObject
{
public:
	ProcessHandleImpl(pid_t pid);
	~ProcessHandleImpl();

	pid_t id() const;
	int wait() const;
	int tryWait() const;

private:
	pid_t _pid;
};


class Foundation_API ProcessImpl
{
public:
	typedef pid_t PIDImpl;
	typedef std::vector<std::string> ArgsImpl;
	typedef std::map<std::string, std::string> EnvImpl;

	static PIDImpl idImpl();
	static void timesImpl(long& userTime, long& kernelTime);
	static ProcessHandleImpl* launchImpl(
		const std::string& command,
		const ArgsImpl& args,
		const std::string& initialDirectory,
		Pipe* inPipe,
		Pipe* outPipe,
		Pipe* errPipe,
		const EnvImpl& env);
	static void killImpl(ProcessHandleImpl& handle);
	static void killImpl(PIDImpl pid);
	static bool isRunningImpl(const ProcessHandleImpl& handle);
	static bool isRunningImpl(PIDImpl pid);
	static void requestTerminationImpl(PIDImpl pid);

private:
	static ProcessHandleImpl* launchByForkExecImpl(
		const std::string& command,
		const ArgsImpl& args,
		const std::string& initialDirectory,
		Pipe* inPipe,
		Pipe* outPipe,
		Pipe* errPipe,
		const EnvImpl& env);
};


} // namespace Poco


#endif // Core_Process_UNIX_INCLUDED
