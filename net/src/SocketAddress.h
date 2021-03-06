/*
	SocketAddress.h - Definition of the SocketAddress class.
*/


#ifndef Net_SocketAddress_INCLUDED
#define Net_SocketAddress_INCLUDED


#include "Net.h"
#include "SocketDefs.h"
#include "IPAddress.h"
//#include "Poco/Net/SocketAddressImpl.h"
#include <ostream>
#include <iostream>


namespace Poco {

class BinaryReader;
class BinaryWriter;

namespace Net {

	struct SockAddr {

#if _WIN32
		typedef u_short sa_family_t;
		typedef u_short in_port_t;
#endif

		struct SockAddrIPv4 {
			in_port_t 	sin_port = 0;
			in_addr		sin_addr;
		};

#if defined(POCO_HAVE_IPv6)
		struct SockAddrIPv6 {
			in_port_t 	sin_port = 0;
			in6_addr	sin_addr;
			uint32_t	sin_scope_id;
		};
#endif

#if defined(POCO_OS_FAMILY_UNIX)
		struct SockAddrUnix {
			char		sun_path[108];
		};
#endif

		sa_family_t	sin_family = AF_UNSPEC;

		union
		{
			SockAddrIPv4 ipv4;
#if defined(POCO_HAVE_IPv6)
			SockAddrIPv6 ipv6;
#endif
#if defined(POCO_OS_FAMILY_UNIX)
			SockAddrUnix local;
#endif
		};

		SockAddr()
			: ipv4(SockAddrIPv4() )
		{}

		SockAddr& operator=(SockAddrIPv4 const& a)
		{
			sin_family = AF_INET;
			ipv4.sin_port = a.sin_port;
			ipv4.sin_addr = a.sin_addr;
			return *this;
		}

#if defined(POCO_HAVE_IPv6)
		SockAddr& operator=(SockAddrIPv6 const& a)
		{
			sin_family = AF_INET6;
			ipv6.sin_port = a.sin_port;
			ipv6.sin_addr = a.sin_addr;
			ipv6.sin_scope_id = a.sin_scope_id;
			return *this;
		}
#endif

#if defined(POCO_OS_FAMILY_UNIX)
		SockAddr& operator=(SockAddrUnix const& a) {
			sin_family = AF_UNIX;
			strncpy(local.sun_path, a.sun_path, strlen(a.sun_path));
			return *this;
		}
#endif
	};


class IPAddress;

/// This class represents an internet (IP) endpoint/socket
/// address. The address can belong either to the
/// IPv4 or the IPv6 address family and consists of a
/// host address and a port number.
class Net_API SocketAddress {
public:
	// The following declarations keep the Family type
	// backwards compatible with the previously used
	// enum declaration.
	using Family = AddressFamily::Family;
	static const Family IPv4 = AddressFamily::IPv4;
#if defined(POCO_HAVE_IPv6)
	static const Family IPv6 = AddressFamily::IPv6;
#endif
#if defined(POCO_OS_FAMILY_UNIX)
	static const Family UNIX_LOCAL = AddressFamily::UNIX_LOCAL;
#endif

	SocketAddress();
		/// Creates a wildcard (all zero) IPv4 SocketAddress.

	explicit SocketAddress(Family family);
		/// Creates a SocketAddress with unspecified (wildcard) IP address
		/// of the given family.

	SocketAddress(const IPAddress& hostAddress, Poco::UInt16 portNumber);
		/// Creates a SocketAddress from an IP address and given port number.

	explicit SocketAddress(Poco::UInt16 port);
		/// Creates a SocketAddress with unspecified (wildcard) IP address
		/// and given port number.

	SocketAddress(Family family, Poco::UInt16 port);
		/// Creates a SocketAddress with unspecified (wildcard) IP address
		/// of the given family, and given port number.

	SocketAddress(const std::string& hostAddress, Poco::UInt16 portNumber);
		/// Creates a SocketAddress from an IP address and given port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.

	SocketAddress(Family family, const std::string& hostAddress, Poco::UInt16 portNumber);
		/// Creates a SocketAddress from an IP address and given port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.
		///
		/// If a domain name is given in hostAddress, it is resolved and the address
		/// matching the given family is used. If no address matching the given family
		/// is found, or the IP address given in hostAddress does not match the given
		/// family, an AddressFamilyMismatchException is thrown.

	SocketAddress(const std::string& hostAddress, const std::string& portNumber);
		/// Creates a SocketAddress from an IP address and the
		/// service name or port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.
		///
		/// The given port must either be a decimal port number, or
		/// a service name.

	SocketAddress(Family family, const std::string& hostAddress, const std::string& portNumber);
		/// Creates a SocketAddress from an IP address and the
		/// service name or port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.
		///
		/// The given port must either be a decimal port number, or
		/// a service name.
		///
		/// If a domain name is given in hostAddress, it is resolved and the address
		/// matching the given family is used. If no address matching the given family
		/// is found, or the IP address given in hostAddress does not match the given
		/// family, an AddressFamilyMismatchException is thrown.

	explicit SocketAddress(const std::string& hostAndPort);
		/// Creates a SocketAddress from an IP address or host name and the
		/// port number/service name. Host name/address and port number must
		/// be separated by a colon. In case of an IPv6 address,
		/// the address part must be enclosed in brackets.
		///
		/// Examples:
		///     192.168.1.10:80
		///     [::ffff:192.168.1.120]:2040
		///     www.appinf.com:8080
		///
		/// On POSIX platforms supporting UNIX_LOCAL sockets, hostAndPort
		/// can also be the absolute path of a local socket, starting with a
		/// slash, e.g. "/tmp/local.socket".

	SocketAddress(Family family, const std::string& addr);
		/// Creates a SocketAddress of the given family from a
		/// string representation of the address, which is
		/// either an IP address and port number, separated by
		/// a colon for IPv4 or IPv6 addresses, or a path for
		/// UNIX_LOCAL sockets.

	SocketAddress(const SocketAddress& addr);
		/// Creates a SocketAddress by copying another one.

	SocketAddress(const struct sockaddr* addr, poco_socklen_t length);
		/// Creates a SocketAddress from a native socket address.

	~SocketAddress();
		/// Destroys the SocketAddress.

	SocketAddress& operator = (const SocketAddress& socketAddress);
		/// Assigns another SocketAddress.

	IPAddress host() const;
		/// Returns the host IP address.

	Poco::UInt16 port() const;
		/// Returns the port number.

	poco_socklen_t length() const;
		/// Returns the length of the internal native socket address.

	const struct sockaddr* addr() const;
		/// Returns a pointer to the internal native socket address.

	int af() const;
		/// Returns the address family (AF_INET or AF_INET6) of the address.

	std::string toString() const;
		/// Returns a string representation of the address.

	Family family() const;
		/// Returns the address family of the host's address.

	bool operator < (const SocketAddress& socketAddress) const;
	bool operator == (const SocketAddress& socketAddress) const;
	bool operator != (const SocketAddress& socketAddress) const;

	enum
	{
		MAX_ADDRESS_LENGTH =
#if defined(POCO_OS_FAMILY_UNIX)
			sizeof(struct sockaddr_un)
#elif defined(POCO_HAVE_IPv6)
			sizeof(struct sockaddr_in6)
#else
			sizeof(struct sockaddr_in)
#endif
			/// Maximum length in bytes of a socket address.
	};

protected:
	bool init(const IPAddress& hostAddress, Poco::UInt16 portNumber);
	bool init(const std::string& hostAddress, Poco::UInt16 portNumber);
	bool init(Family family, const std::string& hostAddress, Poco::UInt16 portNumber);
	bool init(Family family, const std::string& address);
	bool init(const std::string& hostAndPort);
	Poco::UInt16 resolveService(const std::string& service);

private:
	//typedef Poco::Net::Impl::SocketAddressImpl Impl;
	//typedef Poco::AutoPtr<Impl> Ptr;

	//Ptr pImpl() const;

	SockAddr sockAddr;

	void newIPv4();
	void newIPv4(const sockaddr_in*);
	void newIPv4(const IPAddress& hostAddress, Poco::UInt16 portNumber);

#if defined(POCO_HAVE_IPv6)
	void newIPv6(const sockaddr_in6*);
	void newIPv6(const IPAddress& hostAddress, Poco::UInt16 portNumber);
#endif

#if defined(POCO_OS_FAMILY_UNIX)
	void newLocal(const sockaddr_un* sockAddr);
	void newLocal(const std::string& path);
#endif

	//Ptr _pImpl;
};


//
// inlines
//
/* inline SocketAddress::Ptr SocketAddress::pImpl() const
{
	if (_pImpl) return _pImpl;
	throw Poco::NullPointerException("Pointer to SocketAddress implementation is NULL.");
}


inline void SocketAddress::newIPv4()
{
	_pImpl = new Poco::Net::Impl::IPv4SocketAddressImpl;
}


inline void SocketAddress::newIPv4(const sockaddr_in* sockAddr)
{
	_pImpl = new Poco::Net::Impl::IPv4SocketAddressImpl(sockAddr);
}


inline void SocketAddress::newIPv4(const IPAddress& hostAddress, Poco::UInt16 portNumber)
{
	// debug
	std::cout << "SocketAddress newIPv4. Port: " << portNumber << std::endl;
	if (hostAddress.family() == Poco::Net::AddressFamily::IPv4) {
		std::cout << "IPAddress is IPv4." << std::endl;
	}

	_pImpl = new Poco::Net::Impl::IPv4SocketAddressImpl(hostAddress.addr(), htons(portNumber));

	// debug
	std::cout << "After constructor Port: " << _pImpl->port() << std::endl;
	std::cout << "Socket address: ";
	std::cout << std::ios::hex;
	for (int32_t i = 0; i < 16; ++i) {
		std::cout << (uint16_t) (_pImpl->addr()->sa_data)[i] << " ";
	}

	std::cout << std::ios::dec << std::endl;
}


#if defined(POCO_HAVE_IPv6)
inline void SocketAddress::newIPv6(const sockaddr_in6* sockAddr)
{
	_pImpl = new Poco::Net::Impl::IPv6SocketAddressImpl(sockAddr);
}


inline void SocketAddress::newIPv6(const IPAddress& hostAddress, Poco::UInt16 portNumber)
{
	_pImpl = new Poco::Net::Impl::IPv6SocketAddressImpl(hostAddress.addr(), htons(portNumber), hostAddress.scope());
}
#endif // POCO_HAVE_IPv6


#if defined(POCO_OS_FAMILY_UNIX)
inline void SocketAddress::newLocal(const sockaddr_un* sockAddr)
{
	_pImpl = new Poco::Net::Impl::LocalSocketAddressImpl(sockAddr);
}


inline void SocketAddress::newLocal(const std::string& path)
{
	_pImpl = new Poco::Net::Impl::LocalSocketAddressImpl(path.c_str(), path.size());
}
#endif // POCO_OS_FAMILY_UNIX */


inline 	bool SocketAddress::operator == (const SocketAddress& socketAddress) const
{
#if defined(POCO_OS_FAMILY_UNIX)
	if (family() == UNIX_LOCAL)
		return toString() == socketAddress.toString();
	else
#endif
		return host() == socketAddress.host() && port() == socketAddress.port();
}


inline bool SocketAddress::operator != (const SocketAddress& socketAddress) const
{
	return !(operator == (socketAddress));
}


} } // namespace Poco::Net


Net_API Poco::BinaryWriter& operator << (Poco::BinaryWriter& writer, const Poco::Net::SocketAddress& value);
Net_API Poco::BinaryReader& operator >> (Poco::BinaryReader& reader, Poco::Net::SocketAddress& value);
Net_API std::ostream& operator << (std::ostream& ostr, const Poco::Net::SocketAddress& address);


#endif // Net_SocketAddress_INCLUDED
