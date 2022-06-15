#pragma once

#include <string>

#define DYNLIB_HANDLE void *

class DynLib
{
public:
	explicit DynLib(std::string name);
	~DynLib() = default;

	void load(bool bOptional);
	void unload();

	const std::string& getName() const
	{
		return mName;
	}

	bool isLoaded() const;

	void* getSymbol(const std::string& strName) const noexcept;

protected:
	std::string mName;

	static std::string dynlibError();

protected:
	DYNLIB_HANDLE mInst;
};
