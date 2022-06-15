#include "dynlib_manager.h"
#include "dynlib.h"
#include <cassert>

template<>
DynLibManager* Singleton<DynLibManager>::msSingleton = nullptr;

DynLibManager* DynLibManager::getSingletonPtr()
{
	return msSingleton;
}

DynLibManager& DynLibManager::getSingleton()
{
	assert(msSingleton);
	return (*msSingleton);
}

DynLib* DynLibManager::load(const std::string& filename, bool bOptional)
{
	auto i = mLibList.find(filename);
	if (i != mLibList.end())
	{
		return i->second;
	}
	else
	{
		auto* pLib = new DynLib(filename);
		pLib->load(bOptional);
		mLibList[filename] = pLib;
		return pLib;
	}
}

void DynLibManager::unload(DynLib* lib)
{
	auto i = mLibList.find(lib->getName());
	if (i != mLibList.end())
	{
		mLibList.erase(i);
	}
	lib->unload();
	delete lib;
}

DynLibManager::~DynLibManager()
{
	for (auto& it : mLibList)
	{
		it.second->unload();
		delete it.second;
	}

	mLibList.clear();
}
