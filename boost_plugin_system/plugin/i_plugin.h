#pragma once

#include <boost/config.hpp>
#include <string>

class BOOST_SYMBOL_VISIBLE IPlugin
{
public:
	IPlugin() = default;
	virtual ~IPlugin() = default;

	virtual std::string name() const = 0;

	using Ptr = boost::shared_ptr<IPlugin>;
};

typedef IPlugin::Ptr (plugin_create_t)();
