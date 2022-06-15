#include "plugin.h"
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include <boost/make_shared.hpp>

namespace detail
{

	class PluginA final : public IPlugin
	{
	public:
		PluginA() = default;
		~PluginA() final = default;
		std::string name() const final
		{
			return "PluginA";
		}
		static IPlugin::Ptr create()
		{
			return boost::make_shared<PluginA>();
		}
	};

	class PluginB final : public IPlugin
	{
	public:
		PluginB() = default;
		~PluginB() final = default;
		std::string name() const final
		{
			return "PluginB";
		}
		static IPlugin::Ptr create()
		{
			return boost::make_shared<PluginB>();
		}
	};

	class PluginC final : public IPlugin
	{
	public:
		PluginC() = default;
		~PluginC() final = default;
		std::string name() const final
		{
			return "PluginC";
		}
		static IPlugin::Ptr create()
		{
			return boost::make_shared<PluginC>();
		}
	};

	IPlugin::Ptr create_plugin_a()
	{
		// std::cout << "create_plugin" << std::endl;
		return PluginA::create();
	}
	IPlugin::Ptr create_plugin_b()
	{
		// std::cout << "create_plugin" << std::endl;
		return PluginB::create();
	}
	IPlugin::Ptr create_plugin_c()
	{
		// std::cout << "create_plugin" << std::endl;
		return PluginC::create();
	}

}

extern "C" BOOST_SYMBOL_EXPORT detail::PluginA plugin_a;
detail::PluginA plugin_a;

extern "C" BOOST_SYMBOL_EXPORT detail::PluginB plugin_b;
detail::PluginB plugin_b;

extern "C" BOOST_SYMBOL_EXPORT detail::PluginC plugin_c;
detail::PluginC plugin_c;

extern "C" BOOST_SYMBOL_EXPORT detail::PluginA plugin;
detail::PluginA plugin;
