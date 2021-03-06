#pragma once

#include <thread>
#include <vector>
using std::thread;
using std::vector;

class MultiThreadedWorker {
public:
	MultiThreadedWorker();
	~MultiThreadedWorker();

	void startup(int);
	void startup();
	bool run();
	void clear();
	void shutdown();
	bool finished;

protected:
	//fill in tasks list for each worker.
	virtual void generateTasks() = 0;
	int threadCount;
	vector<void*> *tasks;

	//function for each task
	virtual void runTask(void*, int) = 0;

	//after all tasks
	virtual void finishTasks() = 0;


private:
	thread* workers;
	bool *workerStart, *workerFinish;
	bool killAllWorkers;
	void workerFunction(int);
};

