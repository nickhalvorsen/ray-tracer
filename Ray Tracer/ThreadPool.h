#pragma once

#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>

class ThreadPool
{
public:
	ThreadPool(int maxThreads);
	~ThreadPool();
	void addJobToQueue(std::function<void(void)> job);
	void waitUntilComplete();
protected:
	void threadEntry();
	std::mutex lock;
	std::condition_variable condVar;
	bool shutdown;
	std::queue <std::function <void(void)>> jobs;
	std::vector <std::thread> threads;
};