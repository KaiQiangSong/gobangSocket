#ifndef Mutex_H
#define Mutex_H

#include <pthread.h>
#include <mutex>

class Mutex
{
public:
	Mutex();
	Mutex(const Mutex&);
	~Mutex();

	void Lock();
	void Unlock();
	Mutex& operator = (Mutex mtex);

private:
	pthread_mutex_t m_Mutex;
};

#endif