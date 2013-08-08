
#include "sockets.h"

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
#include <string>

UnixClient::UnixClient() {
	char * localhost = new char[10];
	strcpy(localhost, "127.0.0.1");
	setIP(localhost);
	setPort(12345);
	setLogStream(&std::cout);
}

UnixClient::UnixClient(char* ip, unsigned short port) {
	setIP(ip);
	setPort(port);
	setLogStream(&std::cout);
}

UnixClient::UnixClient(char* ip, unsigned short port, std::ostream log) {
	setIP(ip);
	setPort(port);
	setLogStream(&log);
}

char* UnixClient::getIP() {
	return ip;
}

unsigned short UnixClient::getPort() {
	return port;
}

std::ostream* UnixClient::getLogStream() {
	return log;
}

void UnixClient::setIP(char* ip) {
	this->ip = ip;
}

void UnixClient::setPort(unsigned short int port) {
	this->port = port;
}

void UnixClient::setLogStream(std::ostream* log) {
	this->log = log;
}

void UnixClient::start() {
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	sock.used_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock.used_sock < 0) {
		*log << "Failed to create Socket. Error code (Unix): " << sock.used_sock << std::endl;
		return;
	} else {
		*log << "Successfully created socket!" << std::endl;
	}
	
	server = gethostbyname(getIP());
	if(server == NULL) {
		*log << "Unable to resolve host: " << getIP() << std::endl;
		return;
	} else {
		*log << "Resolved host!" << std::endl;
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(getPort());
	if(connect(sock.used_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		*log << "Unable to connect to " << getPort() << "@" << getIP() << std::endl;
		return;
	} else {
		*log << "Connection etablished successfull" << std::endl;
	}
	connected = true;
}

bool UnixClient::isConnected() {
	return connected;
}

void UnixClient::readFromStream(char* buffer, int bufferLength) {
	read(sock.used_sock, buffer, bufferLength);
}

void UnixClient::writeToStream(const char* buffer, int bufferLength) {
	write(sock.used_sock, buffer, bufferLength);
}