#include "ServerNode.h"
#include "../Network/ImagePacket.h"

ServerNode::ServerNode(void) : NetworkNode(SERVER_SEND_TO_PORT, SERVER_RECEIVE_PORT)
{
}


ServerNode::~ServerNode(void)
{
}

unsigned int ServerNode::bufferSize() {
	return 512;
}

void ServerNode::receive( char* buf, unsigned long ip ) {
	ImagePacket image = ImagePacket(buf);
	
}

bool ServerNode::send( int id, int* job, int count, char* ipString ) {
	return true;
}
