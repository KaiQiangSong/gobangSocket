#include "mutex.h"

Mutex::Mutex()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

Mutex::Mutex(const Mutex& mtex)
{
	m_Mutex = mtex.m_Mutex;
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_Mutex);
}

void Mutex::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void Mutex::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}

Mutex& Mutex::operator=(Mutex mtex)
{
	m_Mutex = mtex.m_Mutex;
}