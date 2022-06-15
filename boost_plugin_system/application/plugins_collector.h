#pragma once

#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION

#include <boost/dll/runtime_symbol_info.hpp> // for program_location()
#include <boost/dll/shared_library.hpp>
#include <boost/make_shared.hpp>
#include <boost/container/map.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <utility>

namespace dll = boost::dll;

class plugins_collector
{
	typedef boost::container::map<std::string, dll::shared_library> plugins_t;

	boost::dll::fs::path plugins_directory_;
	plugins_t plugins_;

	void load_all();

	void insert_plugin(BOOST_RV_REF(dll::shared_library) lib);

public:
	explicit plugins_collector(boost::dll::fs::path plugins_directory)
		: plugins_directory_(std::move(plugins_directory))
	{
		load_all();
	}

	void print_plugins() const;

	std::size_t count() const;
};