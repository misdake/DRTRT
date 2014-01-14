#include "JobSet.h"

#include "Main.h"
#include "Player.h"

JobSet::JobSet( char* encodedData ) : jobs(nullptr), buffer(nullptr) {
	float * bufferFloat = (float*)encodedData;
	player->camPosition.x = *bufferFloat++;
	player->camPosition.y = *bufferFloat++;
	player->camPosition.z = *bufferFloat++;
	player->camTarget.x = *bufferFloat++;
	player->camTarget.y = *bufferFloat++;
	player->camTarget.z = *bufferFloat++;

	int * bufferInt = (int*)bufferFloat;
	id = *bufferInt++;
	int count = *bufferInt++;
	jobs = new int[count];
	for(int i=0; i!=count; i++) {
		jobs[i] = *bufferInt++;
	}
}

JobSet::JobSet( int id, vector<int>& jobs ) : jobs(nullptr), buffer(nullptr) {
	int jobCount = jobs.size();
	int length = sizeof(int) + jobCount * sizeof(int) + 6 * sizeof(float);

	buffer = new char[length];

	float * bufferFloat = (float*)buffer;
	*bufferFloat++ = player->camPosition.x;
	*bufferFloat++ = player->camPosition.y;
	*bufferFloat++ = player->camPosition.z;
	*bufferFloat++ = player->camTarget.x;
	*bufferFloat++ = player->camTarget.y;
	*bufferFloat++ = player->camTarget.z;

	int * bufferInt = (int*)bufferFloat;
	*bufferInt++ = id;
	*bufferInt++ = jobCount;
	for(int i=0, size = jobs.size(); i!=size; i++) {
		*bufferInt++ = jobs[i];
	}
}

JobSet::JobSet( int id, int jobCount ) : jobs(nullptr), buffer(nullptr) {
	this->id = id;;
	this->jobCount = jobCount;
	this->jobs = new int[jobCount];
}

JobSet::~JobSet() {
	if(jobs!=nullptr)
		delete[] jobs;
	if(buffer!=nullptr)
		delete[] buffer;
}
