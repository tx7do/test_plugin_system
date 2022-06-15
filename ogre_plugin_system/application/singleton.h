#pragma once

#include <cassert>

template<typename T>
class Singleton
{
public:
	Singleton()
	{
		assert(!msSingleton);
		msSingleton = static_cast<T*>( this );
	}
	~Singleton()
	{
		assert(msSingleton);
		msSingleton = 0;
	}

	Singleton(const Singleton<T>&) = delete;
	Singleton& operator=(const Singleton<T>&) = delete;

	static T& getSingleton()
	{
		assert(msSingleton);
		return (*msSingleton);
	}
	static T* getSingletonPtr()
	{
		return msSingleton;
	}

protected:
	static T* msSingleton;
};
