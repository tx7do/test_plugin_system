#pragma once

#include <string>
#include <cstdint>
#include <vector>

class IPluginManager;

typedef void ( * DLL_START_PLUGIN )(IPluginManager*);

typedef void ( * DLL_STOP_PLUGIN )(IPluginManager*);

#define START_PLUGIN_FUNC_NAME "dllStartPlugin"
#define STOP_PLUGIN_FUNC_NAME "dllStopPlugin"

class IPlugin
{
public:
	IPlugin() = default;
	virtual ~IPlugin() = default;

	virtual const std::string& getType() const = 0;

	virtual const std::string& getName() const = 0;

	virtual void* getObject() const = 0;

	virtual void install() = 0;

	virtual void uninstall() = 0;

	virtual void initialise() = 0;

	virtual void shutdown() = 0;
};

typedef std::vector<IPlugin*> IPluginList;

class IPluginManager
{
public:
	IPluginManager() = default;
	virtual ~IPluginManager() = default;

	virtual void installPlugin(IPlugin* plugin, bool init) = 0;
	virtual void uninstallPlugin(IPlugin* plugin, bool uninit) = 0;

	virtual void initialisePlugins() = 0;
	virtual void shutdownPlugins() = 0;
	virtual void unloadPlugins() = 0;

	virtual const IPluginList& getPlugins() const = 0;
};
