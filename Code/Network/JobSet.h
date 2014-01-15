#pragma once
#include <vector>
using std::vector;

class JobSet
{
public:
	JobSet(){};
	//Build
public:
	JobSet(int id, int jobCount);

	//Decode
public:
	JobSet(char* encodedData);
	int id, jobCount;
	int* jobs;

	//Encode
public:
	JobSet(int id, vector<int>& jobs);
	char * buffer;
	int bufferLen;

public:
	~JobSet();
};

