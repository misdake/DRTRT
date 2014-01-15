#include "ServerPlayer.h"

#include "ImagePacket.h"
#include <thread>
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;

ServerPlayer::ServerPlayer() : Player(), NetworkNode(CLIENT_RECEIVE_PORT, SERVER_RECEIVE_PORT), frameId(0), takeCount(0) {
	valid = nullptr;
}

ServerPlayer::~ServerPlayer() {
	if(valid!=nullptr) {
		delete[] valid;
		valid = nullptr;
	}
}

void ServerPlayer::paint() {

	//time thing.
	static DWORD firstTime = timeGetTime();
	static DWORD time = timeGetTime();
	DWORD last = time;
	time = timeGetTime();
	frameTime = static_cast<float>(time - last) * 0.001f;
	//cout << "frame time = " << time - last << "ms." << endl;

	frameId++;

	memset(valid, 0, height * sizeof(bool));

	//select job set.
	int clientCount = clients.size() + 1;
	vector<int> * jobs = new vector<int>[clientCount];
	for(int i=0; i!=height; i++) {
		if(i < takeCount)
			jobs[0].push_back(i);
		else
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

	//painter.paint();

	//wait & fill unfinished lines.
	fillCount = 0;
	for(int i=height-1; i>=0 ; i--) {
		if(!valid[i]) {
			painter.runTask(i);
			fillCount++;
		}
	}
	takeCount += fillCount;
	takeCount -= takeCount / 4;

	//cout<<"Fill Count = "<<fillCount<<","<<takeCount<<endl;

	for(int i=0; i!=clientCount; i++) {
		//delete jobSets[i];
	}
	delete[] jobSets;
	delete[] jobs;

	if(frameId == 100)
		cout << "frame time = " << timeGetTime() - firstTime << "ms." << endl;
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
