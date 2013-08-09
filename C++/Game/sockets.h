#ifndef SOCKETS_H_
#define SOCKETS_H_

/* Linux/UNIX socket includes */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <list>

typedef struct _socket_address_struct {
	int used_sock;
	int other_sock;
} socket_address;

class UnixSocket {
protected:
	unsigned short port;
	std::ostream* log;
	socket_address sock;
public:
	virtual unsigned short getPort() = 0;
	virtual std::ostream* getLogStream() = 0;
	virtual void setPort(unsigned short port) = 0;
	virtual void setLogStream(std::ostream* log) = 0;
	virtual void start() = 0;
	virtual void readFromStream(char* buffer, int bufferLength) = 0;
	virtual void writeToStream(const char* buffer, int bufferLength) = 0;
	void setRecvTimeout(unsigned long time);
	virtual ~UnixSocket();
};

class UnixClient: public UnixSocket {
	char* ip;
	bool connected = false;
public:
	UnixClient();
	UnixClient(char* ip, unsigned short port);
	UnixClient(char* ip, unsigned short port, std::ostream log);
	char* getIP();
	unsigned short getPort();
	std::ostream* getLogStream();
	void setIP(char* ip);
	void setPort(unsigned short port);
	void setLogStream(std::ostream* log);
	void readFromStream(char* buffer, int bufferLength);
	void writeToStream(const char* buffer, int bufferLength);
	void start();
	bool isConnected();
};

class UnixServer: public UnixSocket {
	socket_address clientSocket;
public:
	UnixServer();
	UnixServer(unsigned short port);
	UnixServer(unsigned short port, std::ostream log);
	unsigned short getPort();
	std::ostream* getLogStream();
	void start();
	void setPort(unsigned short port);
	void setLogStream(std::ostream* log);
	void readFromStream(char* buffer, int bufferLength);
	void writeToStream(const char* buffer, int bufferLength);
	virtual ~UnixServer();
};

void cleanup();

#endif /* SOCKETS_H_ */
