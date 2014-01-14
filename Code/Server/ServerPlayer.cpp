#include "ServerPlayer.h"

#include "ImagePacket.h"
#include <thread>

ServerPlayer::ServerPlayer() : Player(), NetworkNode(CLIENT_RECEIVE_PORT, SERVER_RECEIVE_PORT) {
	valid = nullptr;
}

ServerPlayer::~ServerPlayer() {
	if(valid!=nullptr) {
		delete[] valid;
	}
}

void ServerPlayer::paint() {
	memset(valid, 0, height * sizeof(bool));

	//select job set.

	//build job sets. dispatch.

	painter.paint(/*jobSet*/);

	for(int i=0; i!=height ; i++)
		while(!valid)
			std::this_thread::yield();
}

void ServerPlayer::combine(int top, float* data) {
	Player::combine(top, data);
	valid[top] = true;
}

void ServerPlayer::receive(char* buf, unsigned long ip) {
	ImagePacket imagePacket(buf);
	combine(imagePacket.job, imagePacket.rawData);
}

void ServerPlayer::load(string fileName) {
	Player::load(fileName);
	valid = new bool[height];
}
