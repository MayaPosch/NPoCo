/*
	LoggingRegistry.h - Definition of the LoggingRegistry class.
*/


#ifndef Core_LoggingRegistry_INCLUDED
#define Core_LoggingRegistry_INCLUDED


#include "Core.h"
#include "AutoPtr.h"
#include "Channel.h"
#include "Formatter.h"
#include "Mutex.h"
#include <map>


namespace Poco {


class Foundation_API LoggingRegistry
	/// A registry for channels and formatters.
	///
	/// The LoggingRegistry class is used for configuring
	/// the logging framework.
{
public:
	LoggingRegistry();
		/// Creates the LoggingRegistry.

	~LoggingRegistry();
		/// Destroys the LoggingRegistry.

	Channel::Ptr channelForName(const std::string& name) const;
		/// Returns the Channel object which has been registered
		/// under the given name.
		///
		/// Throws a NotFoundException if the name is unknown.

	Formatter::Ptr formatterForName(const std::string& name) const;
		/// Returns the Formatter object which has been registered
		/// under the given name.
		///
		/// Throws a NotFoundException if the name is unknown.

	void registerChannel(const std::string& name, Channel::Ptr pChannel);
		/// Registers a channel under a given name.
		/// It is okay to re-register a different channel under an
		/// already existing name.
		
	void registerFormatter(const std::string& name, Formatter::Ptr pFormatter);
		/// Registers a formatter under a given name.
		/// It is okay to re-register a different formatter under an
		/// already existing name.

	void unregisterChannel(const std::string& name);
		/// Unregisters the given channel.
		///
		/// Throws a NotFoundException if the name is unknown.

	void unregisterFormatter(const std::string& name);
		/// Unregisters the given formatter.
		///
		/// Throws a NotFoundException if the name is unknown.

	void clear();
		/// Unregisters all registered channels and formatters.

	static LoggingRegistry& defaultRegistry();
		/// Returns a reference to the default
		/// LoggingRegistry.

private:
	typedef Channel::Ptr ChannelPtr;
	typedef AutoPtr<Formatter> FormatterPtr;
	typedef std::map<std::string, ChannelPtr> ChannelMap;
	typedef std::map<std::string, FormatterPtr> FormatterMap;
	
	ChannelMap   _channelMap;
	FormatterMap _formatterMap;
	mutable FastMutex _mutex;
};


} // namespace Poco


#endif // Core_LoggingRegistry_INCLUDED
