#ifndef SOCKETS_H_
#define SOCKETS_H_

#include <Windows.h>
#include <winsock2.h>
#include <iostream>
#include <list>

class WinSocket {
protected:
	unsigned short port;
	std::ostream* log;
	SOCKET sock;
public:
	virtual unsigned short getPort() = 0;
	virtual std::ostream* getLogStream() = 0;
	virtual void setPort(unsigned short port) = 0;
	virtual void setLogStream(std::ostream* log) = 0;
	virtual void start() = 0;
	virtual void readFromStream(char* buffer, int bufferLength) = 0;
	virtual void writeToStream(const char* buffer, int bufferLength) = 0;
	void setRecvTimeout(unsigned long time);
	virtual ~WinSocket();
};

class WinClient: public WinSocket {
	char* ip;
	bool connected = false;
public:
	WinClient();
	WinClient(char* ip, unsigned short port);
	WinClient(char* ip, unsigned short port, std::ostream log);
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

class WinServer: public WinSocket {
	SOCKET clientSocket;
public:
	WinServer();
	WinServer(unsigned short port);
	WinServer(unsigned short port, std::ostream log);
	unsigned short getPort();
	std::ostream* getLogStream();
	void start();
	void setPort(unsigned short port);
	void setLogStream(std::ostream* log);
	void readFromStream(char* buffer, int bufferLength);
	void writeToStream(const char* buffer, int bufferLength);
	virtual ~WinServer();
};

void cleanup();


#endif /* SOCKETS_H_ */
