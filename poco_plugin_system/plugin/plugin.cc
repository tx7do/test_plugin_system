#include "plugin.h"
#include <Poco/ClassLibrary.h>
#include <iostream>

extern "C" int POCO_LIBRARY_API gimmeFive();

std::string PluginA::name() const
{
	return "PluginA";
}

std::string PluginB::name() const
{
	return "PluginB";
}

std::string PluginC::name() const
{
	return "PluginC";
}

POCO_BEGIN_MANIFEST(IPlugin)
		POCO_EXPORT_CLASS(PluginA)
		POCO_EXPORT_CLASS(PluginB)
		POCO_EXPORT_SINGLETON(PluginC)
POCO_END_MANIFEST

void pocoInitializeLibrary()
{
	std::cout << "TestLibrary initializing" << std::endl;
}

void pocoUninitializeLibrary()
{
	std::cout << "TestLibrary uninitialzing" << std::endl;
}

int gimmeFive()
{
	return 5;
}
