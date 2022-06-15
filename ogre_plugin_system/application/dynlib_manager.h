#pragma once

#include "singleton.h"
#include <string>
#include <map>

class DynLib;

class DynLibManager : public Singleton<DynLibManager>
{
public:
	DynLibManager() = default;
	virtual ~DynLibManager();

	DynLib* load(const std::string& filename, bool bOptional);

	void unload(DynLib* lib);

	static DynLibManager& getSingleton();
	static DynLibManager* getSingletonPtr();

protected:
	typedef std::map<std::string, DynLib*> DynLibList;
	DynLibList mLibList;
};
