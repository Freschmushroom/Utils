 
#include "sockets.h"

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
#include <string>

UnixServer::UnixServer() {
	setPort(12345);
	setLogStream(&std::cout);
}

UnixServer::UnixServer(unsigned short port) {
	setPort(port);
	setLogStream(&std::cout);
}

UnixServer::UnixServer(unsigned short port, std::ostream log) {
	setPort(port);
	setLogStream(&log);
}

unsigned short UnixServer::getPort() {
	return port;
}

std::ostream* UnixServer::getLogStream() {
	return log;
}

void UnixServer::setPort(unsigned short int port) {
	this->port = port;
}

void UnixServer::setLogStream(std::ostream* log) {
	this->log = log;
}

void UnixServer::start() {
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	sock.other_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock.other_sock < 0) {
		*log << "Unable to create socket on port " << getPort() << std::endl;
		return;
	} else {
		*log << "Successfully create socket! Internal Address: " << sock.other_sock << std::endl;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(getPort());
	if(bind(sock.other_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		*log << "Unable to bind socket on port " << getPort() << std::endl;
		return;
 	} else {
		*log << "Successfully bound socket on port " << getPort() << std::endl;
	}
	listen(sock.other_sock, 5);
	clilen = sizeof(cli_addr);
	sock.used_sock = accept(sock.other_sock, (struct sockaddr *) &cli_addr, &clilen);
	if(sock.used_sock < 0) {
		*log << "Unable to accept client!" << std::endl;
		return;
	} else {
		*log << "Accepted client!" << std::endl;
	}
}

void UnixServer::readFromStream(char * buffer, int bufferLength) {
	read(sock.used_sock, buffer, bufferLength);
}

void UnixServer::writeToStream(const char * buffer, int bufferLength) {
	write(sock.used_sock, buffer, bufferLength);
}

UnixServer::~UnixServer() {
	close(sock.used_sock);
	delete log;
}