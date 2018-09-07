#include "pch.h"
#include "Threader.h"

Threader::Threader(int maxThreads)
{
	this->maxThreads = maxThreads;
	threads = std::vector<std::thread>(maxThreads);
}

void Threader::addJobToQueue(std::function<void()> job)
{
	jobs.push_back(job);
}

void Threader::doAllWork()
{
	while (jobs.size() > 0)
	{
		doWork();
	}
}

void Threader::doWork()
{
	// find an available thread
	for (auto&& thread : threads)
	{
		if (thread.joinable()) // "joinable" = still running
			continue;

		thread = std::thread(jobs.back());
		jobs.pop_back();
		return;
	}

	// if not wait for one
	for (auto&& thread : threads)
	{
		if (!thread.joinable())
			continue;

		thread.join();

		thread = std::thread(jobs.back());
		jobs.pop_back();
		return;
	}
}