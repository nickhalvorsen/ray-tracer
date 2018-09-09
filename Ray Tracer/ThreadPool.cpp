#include "pch.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
#include "ThreadPool.h"

using std::bind;
using std::mutex;
using std::function;
using std::unique_lock;

ThreadPool::ThreadPool(int maxThreads) : _shutdown(false)
{
	// Create the specified number of threads
	_threads.reserve(maxThreads);
	for (int i = 0; i < maxThreads; ++i)
		_threads.emplace_back(bind(&ThreadPool::threadEntry, this));
}

ThreadPool::~ThreadPool()
{
	waitUntilComplete();
}

void ThreadPool::waitUntilComplete()
{
	{
		// Unblock all threads and tell them to stop
		unique_lock <mutex> l(_lock);

		_shutdown = true;
		_condVar.notify_all();
	}

	// Wait for all threads to stop
	for (auto& thread : _threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void ThreadPool::addJobToQueue(function <void(void)> job)
{
	unique_lock <mutex> l(_lock);

	_jobs.emplace(move(job));
	_condVar.notify_one();
}


void ThreadPool::threadEntry()
{
	function <void(void)> job;

	while (true)
	{
		{
			unique_lock <mutex> l(_lock);

			while (!_shutdown && _jobs.empty())
				_condVar.wait(l);

			if (_jobs.empty())
			{
				return;
			}

			job = move(_jobs.front());
			_jobs.pop();
		}

		job();
	}

}