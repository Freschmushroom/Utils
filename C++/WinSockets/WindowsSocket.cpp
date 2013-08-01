#include "Sockets.h"
#include <winsock2.h>
#include <iostream>

using std::cout;
using std::endl;

WinSocket::~WinSocket() {
	delete log;
	closesocket(sock);
}

void cleanup() {
	WSACleanup();
}

void WinSocket::setRecvTimeout(unsigned long time) {
	int i = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &time, sizeof(unsigned long));
	if (i) {
		cout << "couldn't set timeout. error code: " << WSAGetLastError() << endl;
	}
}
