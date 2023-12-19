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


int main() {
	std::cout << "Starting UDP server test..." << std::endl;
	
	// Set up UDP server with listening socket.
	uint16_t port = 4004;
	Poco::Net::DatagramSocket udpsocket;
	
	std::cout << "Enable broadcast..." << std::endl;
	
	// Enable UDP broadcast.
	udpsocket.setBroadcast(true);
	
	std::cout << "Socket address & bind..." << std::endl;
	
	// Create socket address instance and bind the UDP socket.
	Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), port);
	udpsocket.bind(sa, true);
	
	std::cout << "Listening loop..." << std::endl;
	
	// Start listening loop.
	bool running = true;
	while (running) {
		// Read data in from socket.
		Poco::Net::SocketAddress sender;
		Poco::Timespan span(250000);
		if (udpsocket.poll(span, Poco::Net::Socket::SELECT_READ)) {
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
