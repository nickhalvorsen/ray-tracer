#include "pch.h"
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <chrono>
#include "ThreadPool.h"

ThreadPool::ThreadPool(int maxThreads) : shutdown(false)
{
	// Create the specified number of threads
	threads.reserve(maxThreads);
	for (int i = 0; i < maxThreads; ++i)
		threads.emplace_back(std::bind(&ThreadPool::threadEntry, this));
}

ThreadPool::~ThreadPool()
{
	waitUntilComplete();
}

void ThreadPool::waitUntilComplete()
{
	{
		// Unblock all threads and tell them to stop
		std::unique_lock <std::mutex> l(lock);

		shutdown = true;
		condVar.notify_all();
	}

	// Wait for all threads to stop
	for (auto& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void ThreadPool::addJobToQueue(std::function <void(void)> job)
{
	std::unique_lock <std::mutex> l(lock);

	jobs.emplace(std::move(job));
	condVar.notify_one();
}


void ThreadPool::threadEntry()
{
	std::function <void(void)> job;

	while (true)
	{
		{
			std::unique_lock <std::mutex> l(lock);

			while (!shutdown && jobs.empty())
				condVar.wait(l);

			if (jobs.empty())
			{
				return;
			}

			job = std::move(jobs.front());
			jobs.pop();
		}

		job();
	}

}