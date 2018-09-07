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
	std::mutex _lock;
	std::condition_variable _condVar;
	bool _shutdown;
	std::queue <std::function <void(void)>> _jobs;
	std::vector <std::thread> _threads;
};