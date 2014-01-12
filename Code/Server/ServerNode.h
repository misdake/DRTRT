#pragma once
#include "../Network/NetworkNode.h"


class ServerNode : public NetworkNode {
private:
	static const unsigned short SERVER_SEND_TO_PORT = 12312;
	static const unsigned short SERVER_RECEIVE_PORT = 12313;
public:
	ServerNode();
	~ServerNode();

	virtual unsigned int bufferSize();

	virtual void receive(char* buf, unsigned long ip);

public:
	bool send(int id, int* job, int count, char* ipString);
};

