#pragma once

class ImagePacket
{
	//Decode
public:
	ImagePacket(char* encodedData);
	int id, job;
	float* rawData;

	//Encode
public:
	ImagePacket(int id, float* rawData, int job);
	char * buffer;
	int bufferLen;

public:
	~ImagePacket();
};

