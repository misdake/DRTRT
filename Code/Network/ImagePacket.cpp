#include "ImagePacket.h"

#include "Main.h"
#include "Player.h"
#include <memory.h>
#include <vector>
using std::vector;

ImagePacket::ImagePacket(char* encodedData) : rawData(nullptr), buffer(nullptr) {
	int * bufferInt = (int*)encodedData;
	id = *bufferInt++;
	job = *bufferInt++;
	int blockCount = *bufferInt++;
	int* colorCount = bufferInt;
	float* colorPointer = (float*)(bufferInt + blockCount);

	int floatCount = 3 * player->width;
	rawData = new float[floatCount];

	int left = 0;
	for(int i=0; i!=blockCount; i++) {

		float r = *colorPointer++;
		float g = *colorPointer++;
		float b = *colorPointer++;

		for(int j=0; j!=colorCount[i]; j++) {
			rawData[left++] = r;
			rawData[left++] = g;
			rawData[left++] = b;
		}

	}
}

ImagePacket::ImagePacket(int id, float* rawData, int job) : rawData(nullptr), buffer(nullptr) {
	vector<int> start;
	float r = -1, g = -1, b = -1;
	int width = player->width;
	for(int i=0; i!=width; i++) {
		if(r != rawData[i*3  ]
		|| g != rawData[i*3+1]
		|| b != rawData[i*3+2]) {
			start.push_back(i);
			r = rawData[i*3  ];
			g = rawData[i*3+1];
			b = rawData[i*3+2];
		}
	}
	int blockCount = start.size();
	start.push_back(width);

	int infoSize = 3 * sizeof(int);
	int rawSize = sizeof(int) * blockCount + 3 * sizeof(float) * blockCount;
	int length = infoSize + rawSize;
	buffer = new char[length];
	bufferLen = length;
	int * bufferInt = (int*)buffer;

	*bufferInt++ = id;
	*bufferInt++ = job;
	*bufferInt++ = blockCount;

	for(int i=0; i!=blockCount; i++) {
		*bufferInt++ = start[i+1] - start[i];
	}
	float * bufferFloat = (float*)bufferInt;
	for(int i=0; i!=blockCount; i++) {
		*bufferFloat++ = rawData[start[i]*3  ];
		*bufferFloat++ = rawData[start[i]*3+1];
		*bufferFloat++ = rawData[start[i]*3+2];
	}
}

ImagePacket::~ImagePacket() {
	if(rawData!=nullptr) {
		delete[] rawData;
		rawData = nullptr;
	}
	if(buffer!=nullptr) {
		delete[] buffer;
		buffer = nullptr;
	}
}