#pragma once

#include <boost/dll/alias.hpp>                          // for BOOST_DLL_ALIAS
#include <boost/shared_ptr.hpp>
#include <string>
#include "i_plugin.h"

namespace detail
{
	IPlugin::Ptr create_plugin_a();
	IPlugin::Ptr create_plugin_b();
	IPlugin::Ptr create_plugin_c();
};

BOOST_DLL_ALIAS(detail::create_plugin_a, create_plugin_a)
BOOST_DLL_ALIAS(detail::create_plugin_b, create_plugin_b)
BOOST_DLL_ALIAS(detail::create_plugin_c, create_plugin_c)

BOOST_DLL_ALIAS(detail::create_plugin_a, create_plugin)
