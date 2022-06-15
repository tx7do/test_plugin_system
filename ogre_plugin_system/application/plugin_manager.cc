#include "plugin_manager.h"
#include "dynlib.h"
#include "dynlib_manager.h"
#include <iostream>

template<>
PluginManager* Singleton<PluginManager>::msSingleton = nullptr;

PluginManager* PluginManager::getSingletonPtr()
{
	return msSingleton;
}

PluginManager& PluginManager::getSingleton()
{
	assert(msSingleton);
	return (*msSingleton);
}

PluginManager::PluginManager()
{
	mDynLibManager = new DynLibManager();
}

PluginManager::~PluginManager()
{
	unloadPlugins();
	delete mDynLibManager;
}

void PluginManager::installPlugin(IPlugin* plugin, bool init)
{
	std::cout << "Plugin installed: " << plugin->getType() << " : " << plugin->getName() << std::endl;

	mPlugins.push_back(plugin);

	plugin->install();

	if (pluginInstalled)
	{
		pluginInstalled(plugin);
	}

	if (init)
	{
		plugin->initialise();
	}
}

void PluginManager::uninstallPlugin(IPlugin* plugin, bool uninit)
{
	auto i = std::find(mPlugins.begin(), mPlugins.end(), plugin);
	if (i == mPlugins.end()) return;

	if (pluginUninstalled)
	{
		pluginUninstalled(plugin);
	}

	if (uninit)
	{
		plugin->shutdown();
	}
	plugin->uninstall();

	mPlugins.erase(i);
}

void PluginManager::initialisePlugins()
{
	for (auto i = mPlugins.begin(); i != mPlugins.end(); ++i)
	{
		(*i)->initialise();
	}
}

void PluginManager::shutdownPlugins()
{
	for (auto i = mPlugins.rbegin(); i != mPlugins.rend(); ++i)
	{
		(*i)->shutdown();
	}
}

void PluginManager::execStartPluginFunc(DynLib* lib)
{
	assert(lib);
	auto pFunc = reinterpret_cast<DLL_STOP_PLUGIN>(lib->getSymbol(START_PLUGIN_FUNC_NAME));
	assert(pFunc);
	//std::cout << "Start plugin func: " << pFunc << std::endl;
	pFunc(this);
}

void PluginManager::execStopPluginFunc(DynLib* lib)
{
	assert(lib);
	auto pFunc = reinterpret_cast<DLL_STOP_PLUGIN>(lib->getSymbol(STOP_PLUGIN_FUNC_NAME));
	assert(pFunc);
	pFunc(this);
}

void PluginManager::unloadPlugins()
{
	for (auto i = mPluginLibs.rbegin(); i != mPluginLibs.rend(); ++i)
	{
		if ((*i)->isLoaded())
		{
			execStopPluginFunc(*i);
		}
		DynLibManager::getSingleton().unload(*i);
	}
	mPluginLibs.clear();

	for (auto i = mPlugins.rbegin(); i != mPlugins.rend(); ++i)
	{
		(*i)->uninstall();
	}
	mPlugins.clear();
}

void PluginManager::loadPlugin(const std::string& pluginName, bool bOptional)
{
	auto lib = DynLibManager::getSingleton().load(pluginName, bOptional);
	//std::cout << "PluginManager::loadPlugin: " << pluginName << lib << std::endl;
	if (std::find(mPluginLibs.begin(), mPluginLibs.end(), lib) != mPluginLibs.end())
	{
		return;
	}



	mPluginLibs.push_back(lib);
	if (!lib->isLoaded())
	{
		std::cout << "load plugin failed: " << lib->getName() << std::endl;
		return;
	}

	try
	{
		execStartPluginFunc(lib);
	}
	catch (std::exception& e)
	{
		if (!bOptional)
		{
			throw;
		}
		else
		{
		}
	}
}

void PluginManager::unloadPlugin(const std::string& pluginName)
{
	for (auto i = mPluginLibs.begin(); i != mPluginLibs.end(); ++i)
	{
		auto item = *i;

		if (item->getName() != pluginName) continue;

		if (item->isLoaded())
		{
			execStartPluginFunc(item);
		}

		DynLibManager::getSingleton().unload(item);
		mPluginLibs.erase(i);

		return;
	}
}

const IPluginList& PluginManager::getPlugins() const
{
	return mPlugins;
}
