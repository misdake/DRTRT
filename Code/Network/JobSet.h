#pragma once
#include <vector>
using std::vector;

class JobSet
{
	//Decode
public:
	JobSet(char* encodedData);
	int id, jobCount;
	int* jobs;

	//Encode
public:
	JobSet(int id, vector<int> jobs);
	char * buffer;

public:
	~JobSet();
};

