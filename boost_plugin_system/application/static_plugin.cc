
#include "static_plugin.h"
#include <boost/make_shared.hpp>
#include <iostream>

namespace detail
{
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

		static IPlugin::Ptr create()
		{
			return boost::make_shared<StaticPlugin>();
		}
	};

	IPlugin::Ptr create_plugin()
	{
		// std::cout << "create_plugin" << std::endl;
		return boost::make_shared<StaticPlugin>();
	}
}
