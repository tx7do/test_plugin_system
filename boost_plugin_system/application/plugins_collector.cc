#include "plugins_collector.h"
#include "plugin_util.h"
#include "i_plugin.h"

void plugins_collector::load_all()
{
	namespace fs = ::boost::dll::fs;
	typedef fs::path::string_type string_type;
	const string_type extension = dll::shared_library::suffix().native();

	fs::recursive_directory_iterator endit;
	for (fs::recursive_directory_iterator it(plugins_directory_); it != endit; ++it)
	{
		if (!fs::is_regular_file(*it))
		{
			continue;
		}
		if (!is_shared_library((*it).path()))
		{
			continue;
		}

		boost::dll::fs::error_code error;
		dll::shared_library plugin(it->path(), error);
		if (error)
		{
			continue;
		}
		std::cout << "Loaded (" << plugin.native() << "):" << it->path() << '\n';

		insert_plugin(boost::move(plugin));
	}

	dll::shared_library plugin(dll::program_location());
	std::cout << "Loaded self\n";
	insert_plugin(boost::move(plugin));
}

void plugins_collector::insert_plugin(BOOST_RV_REF(dll::shared_library) lib)
{
	std::string plugin_name;
	if (lib.has("create_plugin"))
	{
		plugin_name = lib.get_alias<IPlugin::Ptr()>("create_plugin")()->name();
	}
	else if (lib.has("plugin"))
	{
		plugin_name = lib.get<IPlugin>("plugin").name();
	}
	else
	{
		return;
	}

	if (plugins_.find(plugin_name) == plugins_.cend())
	{
		plugins_[plugin_name] = boost::move(lib);
	}
}

void plugins_collector::print_plugins() const
{
	plugins_t::const_iterator const end = plugins_.cend();
	for (plugins_t::const_iterator it = plugins_.cbegin(); it != end; ++it)
	{
		std::cout << '(' << it->second.native() << "): " << it->first << '\n';
	}
}

std::size_t plugins_collector::count() const
{
	return plugins_.size();
}
