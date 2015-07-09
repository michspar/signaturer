#include "stdafx.h"
#include "threadPool.h"


threadPool::threadPool(int nThreads) :
isAlive_(true)
{
	for (int i = 0; i < nThreads; i++)
		threads_.push_back(boost::thread(boost::bind(&threadPool::processQueue, this)));
}

threadPool::~threadPool()
{
	joinQueue();

	isAlive_ = false;

	for (boost::thread &thread : threads_)
		thread.join();
}

void threadPool::queue(boost::function<void()> func)
{
	boost::lock_guard<boost::mutex> lock(m_);
	queue_.push_back(func);
}

void threadPool::processQueue()
{
	while (isAlive_)
	{
		boost::function<void()> func;
		{
			boost::lock_guard<boost::mutex> lock(m_);

			if (!queue_.size())
				continue;

			func = queue_.front();

			queue_.pop_front();
		}

		func();
	}
}

void threadPool::joinQueue()
{
	while (queue_.size())
		boost::this_thread::sleep_for(boost::chrono::nanoseconds(1000000));
}