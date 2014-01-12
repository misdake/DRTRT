#include "JobSet.h"

JobSet::JobSet( char* encodedData ) {

}

JobSet::JobSet( int id, vector<int> jobs ) {
	int jobCount = jobs.size();
	int length = sizeof(int) + jobCount * sizeof(int);

}

JobSet::~JobSet() {

}
