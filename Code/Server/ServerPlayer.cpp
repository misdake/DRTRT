#include "ServerPlayer.h"

#include "ImagePacket.h"
#include <thread>
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;

ServerPlayer::ServerPlayer() : Player(), NetworkNode(CLIENT_RECEIVE_PORT, SERVER_RECEIVE_PORT), frameId(0) {
	valid = nullptr;
}

ServerPlayer::~ServerPlayer() {
	if(valid!=nullptr) {
		delete[] valid;
		valid = nullptr;
	}
}

void ServerPlayer::paint() {
	frameId++;

	memset(valid, 0, height * sizeof(bool));


	//select job set.
	int clientCount = clients.size() + 1;
	vector<int> * jobs = new vector<int>[clientCount];
	for(int i=0; i!=height; i++) {
		jobs[i % clientCount].push_back(i);
	}

	//build job sets. dispatch.
	JobSet ** jobSets = new JobSet*[clientCount];
	for(int i=1; i!=clientCount; i++) {
		jobSets[i] = new JobSet(frameId, jobs[i]);
		send(jobSets[i]->buffer, jobSets[i]->bufferLen, clients[i-1]);
	}

	jobSets[0] = new JobSet(frameId, jobs[0]);
	JobSet job(jobSets[0]->buffer);
	painter.paint(&job);
	
	std::this_thread::yield();

	//delete these two lines. just to test filling hole functionality.
	//JobSet c(0, 0);
	//painter.paint(&c);

	//painter.paint();

	//wait & fill unfinished lines.
	int fillCount = 0;
	for(int i=height-1; i>=0 ; i--) {
		if(!valid[i]) {
			painter.runTask(i);
			fillCount++;
		}
	}
	//cout<<"Fill Count = "<<fillCount<<endl;

	for(int i=0; i!=clientCount; i++) {
		//delete jobSets[i];
	}
	delete[] jobSets;
	delete[] jobs;
}

void ServerPlayer::combine(int top, float* data) {
	if(!valid[top]) {
		Player::combine(top, data);
		valid[top] = true;
	}
}

void ServerPlayer::receive(char* buf, unsigned long ip) {
	ImagePacket imagePacket(buf);
	if(imagePacket.id == frameId)
		combine(imagePacket.job, imagePacket.rawData);
}

void ServerPlayer::load(string fileName) {
	Player::load(fileName);
	valid = new bool[height];
}

void ServerPlayer::loadClientList(string fileName) {
	ifstream input(fileName);
	char line[512];
	while (input.getline(line, 512)) {
		clients.push_back(inet_addr(line));
	}
}
