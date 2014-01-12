#include "Node.h"

#include <iostream>
#pragma comment(lib, "ws2_32.lib")


void Node::error(char* message) {
	int errorNumber = WSAGetLastError();
	std::cout << "Error: " << message << ", code = " << errorNumber << std::endl;
}

int Node::count = 0;
WSADATA Node::wsd;
mutex Node::mtx;
bool Node::wsaReady = false;

bool Node::isReady() {
	return wsaReady;
}

Node::Node() {
	{
		std::unique_lock<mutex> lck(mtx);
		count++;
		if (!wsaReady) {
			if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
				error("WSAStartup");
				return;
			}
			wsaReady = true;
		}
	}

	//---------SEND---------
	//clientSocket
	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		error("创建套接字失败");
		return;
	}


	//---------RECEIVE---------
	//serverSocket
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		error("创建套接字失败");
		return;
	}


	//receiveThread
	receiveRunning = false;
}

Node::~Node() {
	{
		std::unique_lock<mutex> lck(mtx);
		count--;
		if (count <= 0) {
			WSACleanup();//释放套接字资源
			wsaReady = false;
		}
	}
	stop();
}


bool Node::start() {
	if (receiveRunning)
		stop();

	//remoteAddress
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_port = htons(sendPort());
	remoteAddressLen = sizeof(remoteAddress);

	//localAddress
	localAddress.sin_family = AF_INET;
	localAddress.sin_port = htons(receivePort());
	localAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//receiveBuffer
	receiveBuffer = new char[receiveBufferSize()];


	//start receiving thread
	receiveRunning = true;
	receiveStopped = false;
	receiveThread = thread(&Node::receiveFunction, this);

	return true;
}

void Node::stop() {
	receiveRunning = false;
	while (!receiveStopped)
		std::this_thread::yield();

	if (receiveThread.joinable())
		receiveThread.join();

	if (receiveBuffer != nullptr)
		delete [] receiveBuffer;
	receiveBuffer = nullptr;
}

bool Node::send(const char* buf, int len, char* ipString) {
	return send(buf, len, inet_addr(ipString));
}
bool Node::send(const char* buf, int len, unsigned long ip) {
	remoteAddress.sin_addr.s_addr = ip;    //IP
	while (sendto(clientSocket, buf, len, 0, (SOCKADDR*) &remoteAddress, remoteAddressLen) == SOCKET_ERROR) {
		if (WSAEWOULDBLOCK == WSAGetLastError()) {
			//idle

			std::this_thread::yield();
		} else {
			error("发送数据失败");
			closesocket(clientSocket);    //关闭套接字
			return false;
		}
	}

	return true;
}

void Node::receiveFunction() {
	if (!wsaReady)
		return;

	SOCKADDR_IN clientAddress;
	int nClientLen = sizeof(clientAddress);
	//绑定
	if (bind(serverSocket, (SOCKADDR *) &localAddress, sizeof(localAddress)) == SOCKET_ERROR) {
		error("绑定失败");
		closesocket(serverSocket);    //关闭套接字
		return;
	}
	unsigned long mode = 1;  // 1 to enable non-blocking socket
	ioctlsocket(serverSocket, FIONBIO, &mode);

	for (;;) {
		if (!wsaReady || !receiveRunning) {
			break;
		}
		
		bool errorOccured = false;

		//接收数据
		ZeroMemory(receiveBuffer, receiveBufferSize());
		while (recvfrom(serverSocket, receiveBuffer, receiveBufferSize(), 0, (SOCKADDR*) &clientAddress, &nClientLen) == SOCKET_ERROR) {
			if (WSAEWOULDBLOCK == WSAGetLastError()) {
				//idle

				if (!wsaReady || !receiveRunning) {
					errorOccured = true;
					break;
				}

				std::this_thread::yield();
				continue;
			}
			error("接收数据失败");
			closesocket(serverSocket);    //关闭套接字
			errorOccured = true;
			break;
		}

		//data received
		if (!errorOccured)
			receive(receiveBuffer, clientAddress.sin_addr.S_un.S_addr);

	}
	receiveStopped = true;
}
