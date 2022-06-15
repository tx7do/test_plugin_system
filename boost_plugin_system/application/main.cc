#include <boost/dll/import.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/function.hpp>
#include <iostream>

#include "i_plugin.h"

namespace dll = boost::dll;

void test_import_alias()
{
	std::cout << "Call function" << std::endl;

	boost::filesystem::path shared_library_path("libboost_plugin.so");

	auto creator = boost::dll::import_alias<plugin_create_t>(
		shared_library_path,
		"create_plugin",
		dll::load_mode::append_decorations
	);

	//std::cout << "plugin creator ptr: " << creator << std::endl;

	auto plugin = creator();
	std::cout << "plugin ptr: " << plugin << std::endl;
	std::cout << "IPlugin Name:  " << plugin->name() << std::endl;
}

void test_Load_library()
{
	std::cout << "Call function" << std::endl;

	boost::filesystem::path shared_library_path("libboost_plugin.so");
	boost::dll::shared_library lib(shared_library_path);

	auto creator = lib.get_alias<plugin_create_t>("create_plugin");

	//std::cout << "plugin creator ptr: " << creator << std::endl;

	auto plugin = creator();
	std::cout << "plugin ptr: " << plugin << std::endl;
	std::cout << "IPlugin Name:  " << plugin->name() << std::endl;
}

void test_static_plugin()
{
	dll::shared_library self(dll::program_location());

	std::cout << "Call function" << std::endl;

	auto creator = self.get_alias<plugin_create_t>("create_plugin");

	//std::cout << "plugin creator ptr: " << creator << std::endl;

	auto plugin = creator();
	std::cout << "plugin ptr: " << plugin << std::endl;
	std::cout << "IPlugin Name:  " << plugin->name() << std::endl;
}

int main(int argc, char* argv[])
{
	//test_static_plugin();
	test_import_alias();
	//test_Load_library();

	return 0;
}
