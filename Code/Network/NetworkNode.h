#pragma once
#include "Node.h"

class NetworkNode : public Node {
public:
	NetworkNode(unsigned short sendPort, unsigned short receivePort);
	~NetworkNode();

protected:
	unsigned short sport;
	unsigned short rport;

	virtual unsigned int receiveBufferSize();
	virtual unsigned short sendPort();
	virtual unsigned short receivePort();

	virtual void receive(char* buf, unsigned long ip);
};

