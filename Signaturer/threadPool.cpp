#include "stdafx.h"
#include "threadPool.h"


threadPool::threadPool() :
isAlive_(true)
{
	for (int i = 0; i < boost::thread::hardware_concurrency(); i++)
		addProcessingThread();
}

void threadPool::addProcessingThread()
{
	threads_.push_back(boost::thread(boost::bind(&threadPool::processQueue, this)));
}

threadPool::~threadPool()
{
	joinQueue();

	isAlive_ = false;

	for (boost::thread &thread : threads_)
		thread.join();
}

int threadPool::getQueueLimit()
{
	return threads_.size();
}

bool threadPool::isQueueReady()
{
	return queue_.size() <= getQueueLimit();
}

void threadPool::queue(boost::function<void()> func)
{
	boost::unique_lock<boost::mutex> ulock(mQueueReady_);

	while (!isQueueReady())
	{
		isQueueReady_.wait(ulock);
	}

	boost::lock_guard<boost::mutex> lock(m_);
	queue_.push_back(func);
}

void threadPool::processQueue()
{
	while (isAlive_)
	{
		boost::function<void()> func;

		m_.lock();

		if (!queue_.size())
		{
			m_.unlock();
			isQueueEmpty_.notify_all();
			isQueueReady_.notify_all();

			if (threads_.size() > 1)
			{

				boost::unique_lock<boost::mutex> ulock(mQueueReady_);

				while (!isQueueReady())
					isQueueReady_.wait(ulock);
			}

			continue;
		}

		func = queue_.front();

		queue_.pop_front();

		if (isQueueReady())
			isQueueReady_.notify_all();

		m_.unlock();
		func();
	}
}

void threadPool::joinQueue()
{
	boost::unique_lock<boost::mutex> lock(mQueueEmpty_);

	while (queue_.size())
		isQueueEmpty_.wait(lock);
}