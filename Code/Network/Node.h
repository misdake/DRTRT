#pragma once

#include "winsock2.h"
#include <thread>
using std::thread;
#include <mutex>
using std::mutex;

class Node {
public:
	Node();
	~Node();
	bool isReady();

	//Windows only
private:
	static int count;
	static WSADATA wsd;
	static bool wsaReady;
	static mutex mtx;

	//control
public:
	bool start();
	void stop();

	//parameter
protected:
	virtual unsigned short sendPort() = 0;
	virtual unsigned short receivePort() = 0;

	//send
protected:
	bool send(const char* buf, int len, char* ipString); //blocking
	bool send(const char* buf, int len, unsigned long ip); //blocking
private:
	SOCKET clientSocket;
	SOCKADDR_IN remoteAddress;
	int remoteAddressLen;

	//receive
protected:
	virtual void receive(char* buf, unsigned long ip) = 0; //receiveThread
	virtual unsigned int receiveBufferSize() = 0;
private:
	char* receiveBuffer;
	SOCKET serverSocket;
	SOCKADDR_IN localAddress;
	bool receiveRunning;
	bool receiveStopped;
	void receiveFunction();
	thread receiveThread;

	//error
private:
	static void Node::error(char* message);
};

