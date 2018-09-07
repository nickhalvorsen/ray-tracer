#pragma once

#include <vector>
#include <deque>
#include <functional>
#include <mutex>

#include "Bitmap.h"
#include "RenderedImage.h"

class Threader
{
public:
	Threader(int maxThreads);
	void addJobToQueue(std::function<void()> job);
	void doWork();
	void doAllWork();
private:
	std::vector<std::thread> threads;
	std::deque<std::function<void()>> jobs;
	int maxThreads;
	std::mutex workingMutex;
};