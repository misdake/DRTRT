#include "MultiThreadedWorker.h"

MultiThreadedWorker::MultiThreadedWorker() {

}

MultiThreadedWorker::~MultiThreadedWorker() {
	shutdown();
}

void MultiThreadedWorker::startup(int threadCount) {
	this->threadCount = threadCount;
	workers = new thread[threadCount];
	workerStart = new bool[threadCount];
	workerFinish = new bool[threadCount];
	tasks = new vector<void*>[threadCount];
	finished = true;
	killAllWorkers = false;
	for (int i = 0; i != threadCount; i++) {
		workerStart[i] = false;
		workerFinish[i] = false;
		workers[i] = thread(&MultiThreadedWorker::workerFunction, this, i);
	}
}

void MultiThreadedWorker::startup() {
	startup(std::thread::hardware_concurrency());
}

void MultiThreadedWorker::shutdown() {
	if (!killAllWorkers) {
		killAllWorkers = true;
		for (int i = 0; i != threadCount; i++) {
			workers[i].join();
		}
	}
}

bool MultiThreadedWorker::run() {
	if (!finished || killAllWorkers)
		return false;

	finished = false;

	//init
	for (int i = 0; i != threadCount; i++) {
		workerStart[i] = false;
		workerFinish[i] = false;
	}
	generateTasks();
	for (int i = 0; i != threadCount; i++) {
		workerStart[i] = true;
	}
	
	//workers should be working now.

	//wait for all workers to finish.
	for (int i = 0; i != threadCount; i++) {
		while (!workerFinish[i]) {
			std::this_thread::yield();
		}
	}

	//all finished here.
	finishTasks();

	finished = true;
	for (int i = 0; i != threadCount; i++) {
		tasks[i].clear();
	}

	return true;
}

void MultiThreadedWorker::workerFunction(int index) {
	for (;;) {
		//wait for tasks
		while (!workerStart[index]) {
			if (killAllWorkers) {
				return;
			}
			std::this_thread::yield();
		}
		workerStart[index] = false;

		//run
		for (void* task : tasks[index]) {
			runTask(task);
		}

		//finish
		workerFinish[index] = true;
	}
}
