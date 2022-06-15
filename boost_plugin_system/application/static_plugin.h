#pragma once

#include <boost/dll/alias.hpp>                          // for BOOST_DLL_ALIAS
#include <boost/shared_ptr.hpp>
#include "i_plugin.h"

namespace detail
{
	IPlugin::Ptr create_plugin();
}

BOOST_DLL_ALIAS(detail::create_plugin, create_plugin)
