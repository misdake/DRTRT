#include "NetworkNode.h"

#include <iostream>

NetworkNode::NetworkNode(unsigned short sendPort, unsigned short receivePort) {
	this->sport = sendPort;;
	this->rport = receivePort;
}


NetworkNode::~NetworkNode() {
}

unsigned int NetworkNode::receiveBufferSize() {
	return 512;
}
unsigned short NetworkNode::sendPort() {
	return sport;
}
unsigned short NetworkNode::receivePort() {
	return rport;
}

void NetworkNode::receive(char* buf, unsigned long ip) {
	std::cout << "from " << (ip >> 0 & 0xff) << "." << (ip >> 8 & 0xff) << "." << (ip >> 16 & 0xff) << "." << (ip >> 24 & 0xff) << ":" << buf << std::endl;
}
