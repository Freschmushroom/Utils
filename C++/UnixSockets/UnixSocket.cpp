 
#include "sockets.h"

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>

UnixSocket::~UnixSocket() {
	delete log;
	close(sock.used_sock);
	if(sock.other_sock >= 0) {
		close(sock.other_sock);
	}
}

void UnixSocket::setRecvTimeout(unsigned long time) {
	struct timeval timeout;
	timeout.tv_sec = time;
	timeout.tv_usec = 0;
	
	if(setsockopt(sock.used_sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) < 0)
		std::cout << "Couldn't set timeout!" << std::endl;
	
}