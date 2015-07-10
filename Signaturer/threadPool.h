#pragma once
class threadPool
{
	std::list<boost::function<void()>> queue_;
	std::list<boost::thread> threads_;
	bool isAlive_;
	boost::mutex m_, mQueueEmpty_, mQueueReady_;
	boost::condition_variable isQueueEmpty_, isQueueReady_;

	void processQueue();
	void joinQueue();
	void addProcessingThread();
	int getQueueLimit();
	bool isQueueReady();

public:
	threadPool();
	~threadPool();

	void queue(boost::function<void()> func);
};

