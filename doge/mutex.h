#pragma once

#include <pthread.h>
#include "utils.h"
namespace doge
{
namespace details
{
class Mutex : noncopyable
{
public:
	Mutex()
	{
		pthread_mutex_init(&lock_, NULL);
	};
	~Mutex()
	{
		pthread_mutex_destroy(&lock_);
	};

	void Lock()
	{
		pthread_mutex_lock(&lock_);
	};

	void unLock()
	{
		pthread_mutex_unlock(&lock_);
	};
private:
	pthread_mutex_t lock_;
};

class NulMutex : noncopyable
{
public:
	NulMutex() {};
	~NulMutex() {};
	void Lock() {};
	void unLock() {};
};

template<typename _Mutex>
class ScopedLock : noncopyable
{
public:
	ScopedLock(_Mutex & lk): lk_(lk)
	{
		lk_.Lock();
	};

	~ScopedLock()
	{
		lk_.unLock();
	};
private:
	_Mutex & lk_;
};
}
}
