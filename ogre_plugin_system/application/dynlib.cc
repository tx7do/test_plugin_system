#include "dynlib.h"
#include <dlfcn.h>
#include <iostream>
#include <utility>
#include <filesystem>

#define DYNLIB_LOAD(a) dlopen( a, RTLD_LAZY | RTLD_LOCAL )
#define DYNLIB_GETSYM(a, b) dlsym( a, b )
#define DYNLIB_UNLOAD(a) dlclose( a )

DynLib::DynLib(std::string name)
	: mName(std::move(name)), mInst(nullptr)
{
}

void DynLib::load(bool bOptional)
{
	std::string name = std::filesystem::current_path().string() + "/" + mName;

	if (name.find(".so") == std::string::npos)
	{
		name += ".so";
	}

	mInst = (DYNLIB_HANDLE)DYNLIB_LOAD(name.c_str());

//	std::cout << "Loading " << name << " : " << mInst << std::endl;
}

void DynLib::unload()
{
	if (mInst)
	{
		if (DYNLIB_UNLOAD(mInst))
		{
		}
	}
}

bool DynLib::isLoaded() const
{
	return mInst != nullptr;
}

void* DynLib::getSymbol(const std::string& strName) const noexcept
{
	return (void*)DYNLIB_GETSYM(mInst, strName.c_str());
}

std::string DynLib::dynlibError()
{
	const char* errorStr = dlerror();
	if (errorStr)
	{
		return std::string{ errorStr };
	}
	else
	{
		return std::string{ "" };
	}
}
