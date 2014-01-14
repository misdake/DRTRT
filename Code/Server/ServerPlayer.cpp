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

	//server rendering & waiting for clients.
	//painter.paint(/*jobSet*/);

	//delete these two lines. just to test filling hole functionality.
	JobSet c(0, 0);
	painter.paint(&c);

	//wait & fill unfinished lines.
	for(int i=height-1; i>=0 ; i--) {
		if(!valid[i]) {
			painter.runTask(i);
		}
	}
}

void ServerPlayer::combine(int top, float* data) {
	if(!valid[top]) {
		Player::combine(top, data);
		valid[top] = true;
	}
}

void ServerPlayer::receive(char* buf, unsigned long ip) {
	ImagePacket imagePacket(buf);
	combine(imagePacket.job, imagePacket.rawData);
}

void ServerPlayer::load(string fileName) {
	Player::load(fileName);
	valid = new bool[height];
}
