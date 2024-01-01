/*
	udp_server_test.cpp - Simple UDP server test for NPoco.
	
	Revision 0
	
	Features:
			- Sets up UDP server, listens for UDP packet, shuts down when received.
			
	Notes:
			- 
			
	2023/12/19, Maya Posch
*/


#include "../src/DatagramSocket.h"

#include <iostream>
#include <cstdio>


int main() {
	std::cout << "Starting UDP server test..." << std::endl;
	
#if defined(POCO_OS_FAMILY_WINDOWS)
	WORD    version = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(version, &data) != 0) { 
		std::cerr << "Error WSAStartup." << std::endl;
		return 1;
	}
#endif
	
	// Set up UDP server with listening socket.
	uint16_t port = 4004;
	Poco::Net::DatagramSocket udpsocket;
	
	std::cout << "Enable broadcast..." << std::endl;
	
	// Enable UDP broadcast.
	udpsocket.setBroadcast(true);
	
	std::cout << "Socket address & bind..." << std::endl;
	
	// Create socket address instance and bind the UDP socket.
	Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), port);
	//Poco::Net::SocketAddress sa(Poco::Net::IPAddress("127.0.0.1"), port);
	int err = udpsocket.bind(sa, true);
	if (err != 0) {
		std::cout << "Failed to bind to UDP port: " << err << "..." << std::endl;
		perror(NULL);
		//perror("bind");
#ifdef __WIN32
		wchar_t *s = NULL;
		FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | 
					FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, WSAGetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPWSTR)&s, 0, NULL);
		fprintf(stderr, "%S\n", s);
		LocalFree(s);
#endif
		return 1;
	}
	
	std::cout << "Listening loop..." << std::endl;
	
	// Start listening loop.
	bool running = true;
	Poco::Net::SocketAddress sender;
	Poco::Timespan span(250000);
	while (running) {
		// Read data in from socket.
		//std::cout << "DEBUG: Read from socket." << std::endl;
		//Poco::Timespan timeout(0, 100); // 100 microsecond timeout
		if (udpsocket.poll(span, Poco::Net::Socket::SELECT_READ)) {
			std::cout << "DEBUG: in poll." << std::endl;
			char buffer[2048];
			int n = 0;
			n = udpsocket.receiveFrom(buffer, sizeof(buffer), sender);
			
			// Received a packet. Report and quit.
			std::cout << "Received " << n << " bytes. Shutting down..." << std::endl;
			running = false;
		}
	}
	
	return 0;
}
