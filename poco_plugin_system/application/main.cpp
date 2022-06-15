#include "plugin.h"
#include "Poco/ClassLoader.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Manifest.h"
#include "Poco/Exception.h"
#include <iostream>

typedef int (* GimmeFiveFunc)();

typedef bool (* pocoBuildManifestFunc)(Poco::ManifestBase*);

typedef void (* pocoInitializeLibraryFunc)();

typedef void (* pocoUninitializeLibraryFunc)();

void testClassLoader()
{
	std::string path = "./libpoco_plugin" + Poco::SharedLibrary::suffix();

	std::cout << "Load lib:  " << path << std::endl;

	Poco::ClassLoader<IPlugin> cl;
	cl.loadLibrary(path);


	auto pPluginA = cl.classFor("PluginA").create();
	std::cout << "PluginA Name:  " << pPluginA->name() << std::endl;

	auto pPluginB = cl.classFor("PluginB").create();
	std::cout << "PluginB Name:  " << pPluginB->name() << std::endl;

	auto& pPluginC = cl.instance("PluginC");
	std::cout << "PluginC Name:  " << pPluginC.name() << std::endl;

	// 必须要手动释放，否则不会释放动态库
	cl.unloadLibrary(path);
}

void testSharedLibrary()
{
	std::string path = "./libpoco_plugin" + Poco::SharedLibrary::suffix();
	std::cout << "Load lib:  " << path << std::endl;

	Poco::SharedLibrary sl;
	sl.load(path);
	std::cout << "Loaded:  " << sl.isLoaded() << std::endl;

	auto gimmeFive = (GimmeFiveFunc)sl.getSymbol("gimmeFive");
	std::cout << "gimmeFive:  " << gimmeFive() << std::endl;


	auto pManifest = new Poco::Manifest<IPlugin>();
	auto _pocoBuildManifest = (pocoBuildManifestFunc)sl.getSymbol("pocoBuildManifest");
	_pocoBuildManifest(pManifest);
	std::cout << "Manifest Name:  " << std::string(pManifest->className()) << std::endl;
	std::cout << "Class count:  " << pManifest->size() << std::endl;

	auto classPluginA = pManifest->find("PluginA");
	std::cout << "PluginA:  " << (*classPluginA)->name() << std::endl;

	auto classPluginB = pManifest->find("PluginB");
	std::cout << "PluginB:  " << (*classPluginB)->name() << std::endl;

	auto classPluginC = pManifest->find("PluginC");
	std::cout << "PluginC:  " << (*classPluginC)->instance().name() << std::endl;

	auto _pocoInitializeLibrary = (pocoInitializeLibraryFunc)sl.getSymbol("pocoInitializeLibrary");
	_pocoInitializeLibrary();

	auto _pocoUninitializeLibrary = (pocoUninitializeLibraryFunc)sl.getSymbol("pocoUninitializeLibrary");
	_pocoUninitializeLibrary();

	sl.unload();
}

void testStaticPlugin()
{
	pocoInitializeLibrary();
	pocoUninitializeLibrary();

	auto pManifest = new Poco::Manifest<IPlugin>();
	pocoBuildManifest(pManifest);
	std::cout << "Manifest Name:  " << std::string(pManifest->className()) << std::endl;
	std::cout << "Class count:  " << pManifest->size() << std::endl;

	auto classStaticPlugin = pManifest->find("StaticPlugin");
	std::cout << "StaticPlugin:  " << (*classStaticPlugin)->name() << std::endl;
}

int main()
{
//	testSharedLibrary();
//	testClassLoader();
	testStaticPlugin();
	return 0;
}