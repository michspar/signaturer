#pragma once
class threadPool
{
	std::list<boost::function<void()>> queue_;
	std::list<boost::thread> threads_;
	bool isAlive_;
	boost::mutex m_;

	void processQueue();
	void joinQueue();

public:
	threadPool(int nThreads);
	~threadPool();

	void queue(boost::function<void()> func);
};

