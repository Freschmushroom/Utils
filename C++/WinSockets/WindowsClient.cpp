#include "Sockets.h"
#include <Windows.h>
#include <winsock2.h>
#include <iostream>
#include <string>

WinClient::WinClient() {
	char* localhost = new char[10];
	strcpy(localhost, "127.0.0.1");
	setIP(localhost);
	setPort(12345);
	setLogStream(&std::cout);
}

WinClient::WinClient(char* ip, unsigned short port) {
	setIP(ip);
	setPort(port);
	setLogStream(&std::cout);
}

WinClient::WinClient(char* ip, unsigned short port, std::ostream log) {
	setIP(ip);
	setPort(port);
	setLogStream(&log);
}

char* WinClient::getIP() {
	return ip;
}

unsigned short WinClient::getPort() {
	return port;
}

std::ostream* WinClient::getLogStream() {
	return log;
}

void WinClient::setIP(char* ip) {
	this->ip = ip;
}

void WinClient::setPort(unsigned short int port) {
	this->port = port;
}

void WinClient::setLogStream(std::ostream* log) {
	this->log = log;
}

void WinClient::start() {
	WSADATA wsadata;
	int error = WSAStartup(MAKEWORD(2, 0), &wsadata);
	if (error != 0) {
		*log << "Failed to start WSA. Error code: " << error << std::endl;
		return;
	} else {
		*log << "Successfully started WSA." << std::endl;
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		*log << "Failed to create socket. Error code: " << WSAGetLastError() << std::endl;
		return;
	} else {
		*log << "Successfully created socket." << std::endl;
	}


	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);
	error = connect(sock, (SOCKADDR*) &addr, sizeof(SOCKADDR));
	if (error == SOCKET_ERROR) {
		*log << "Failed to connect to " << ip << ":" << port << std::endl;
		return;
	} else {
		*log << "Successfully connected to " << ip << ":" << port << std::endl;
	}
	connected = true;
}

bool WinClient::isConnected() {
	return connected;
}

void WinClient::readFromStream(char* buffer, int bufferLength) {
	recv(sock, buffer, bufferLength, 0);
}

void WinClient::writeToStream(const char* buffer, int bufferLength) {
	send(sock, buffer, bufferLength, 0);
}
