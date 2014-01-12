#include "ImagePacket.h"

#include <memory.h>

ImagePacket::ImagePacket(char* encodedData) {
	int * bufferInt = (int*)encodedData;
	id = *bufferInt++;
	job = *bufferInt++;

	int infoSize = 5 * sizeof(int);
	int rawSize = 3 * sizeof(float) * 480;
	int floatCount = 3 * 480;

	rawData = new float[floatCount];
	memcpy(rawData, encodedData + infoSize, rawSize);

	this->buffer = nullptr;
}

ImagePacket::ImagePacket(int id, float* rawData, int job) {
	int infoSize = 2 * sizeof(int);
	int rawSize = 3 * sizeof(float) * 480;
	int length = infoSize + rawSize;
	buffer = new char[length];
	int * bufferInt = (int*)buffer;

	*bufferInt++ = id;
	*bufferInt++ = job;

	memcpy(buffer + infoSize, rawData, rawSize);

	this->rawData = nullptr;
}

ImagePacket::~ImagePacket() {
	if(rawData!=nullptr) {
		delete[] rawData;
	}
	if(buffer!=nullptr) {
		delete[] buffer;
	}
}