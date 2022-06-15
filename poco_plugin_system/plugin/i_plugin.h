#pragma once

#include <string>

class IPlugin
{
public:
	IPlugin() = default;
	virtual ~IPlugin() = default;
	virtual std::string name() const = 0;
};
