#include "ClientPlayer.h"

#include "ImagePacket.h"
#include <iostream>
using std::cout;
using std::endl;

ClientPlayer::ClientPlayer() : Player(), NetworkNode(SERVER_RECEIVE_PORT, CLIENT_RECEIVE_PORT) {
}

ClientPlayer::~ClientPlayer() {
}

void ClientPlayer::combine(int top, float* data) {
	ImagePacket imagePacket(frameId, data, top);
	send(imagePacket.buffer, imagePacket.bufferLen, ip);
}

bool tt = false;
thread t;
void paintJob(Painter* painter, JobSet* jobSet) {
	painter->paint(jobSet);
	delete jobSet;
}

void ClientPlayer::receive(char* buf, unsigned long ip) {
	painter.clear();
	if(tt)
		t.join();
	this->ip = ip;
	JobSet * jobSet = new JobSet(buf);
	cout << "Frame id = " << jobSet->id <<", Receive JobSet, " << jobSet->jobCount << " jobs, Server IP = " << (ip&(0xff)) << "." << ((ip>>8)&(0xff)) << "." << ((ip>>16)&(0xff)) << "." << (ip>>24) << endl;
	frameId = jobSet->id;
	t = thread(paintJob, &painter, jobSet);
	tt = true;
}