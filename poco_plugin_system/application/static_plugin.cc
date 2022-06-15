
#include "static_plugin.h"
#include <Poco/ClassLibrary.h>
#include <iostream>

class StaticPlugin : public IPlugin
{
public:
	StaticPlugin()
	{
		std::cout << "Constructing StaticPlugin" << std::endl;
	}
	~StaticPlugin() override
	{
		std::cout << "Destructing StaticPlugin" << std::endl;
	}

	std::string name() const override
	{
		return "StaticPlugin";
	}
};

POCO_BEGIN_MANIFEST(IPlugin)
		POCO_EXPORT_CLASS(StaticPlugin)
		//POCO_EXPORT_SINGLETON(StaticPlugin)
POCO_END_MANIFEST

void pocoInitializeLibrary()
{
	std::cout << "Application initializing" << std::endl;
}

void pocoUninitializeLibrary()
{
	std::cout << "Application uninitialzing" << std::endl;
}
