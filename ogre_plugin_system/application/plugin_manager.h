#pragma once

#include "i_plugin.h"
#include "singleton.h"
#include <vector>
#include <functional>

class DynLib;
class DynLibManager;

class PluginManager final : public IPluginManager, public Singleton<PluginManager>
{
public:
	PluginManager();
	~PluginManager() override;

	static PluginManager& getSingleton();
	static PluginManager* getSingletonPtr();

	std::function<void(IPlugin*)> pluginInstalled = nullptr;
	std::function<void(IPlugin*)> pluginUninstalled = nullptr;

public:
	/// 加载插件
	void loadPlugin(const std::string& pluginName, bool bOptional);

	/// 卸载插件
	void unloadPlugin(const std::string& pluginName);

public:
	/// 安装插件
	void installPlugin(IPlugin* plugin, bool init) override;

	/// 卸载插件
	void uninstallPlugin(IPlugin* plugin, bool uninit) override;

public:
	/// 初始化所有插件
	void initialisePlugins() override;

	/// 关闭所有插件
	void shutdownPlugins() override;

	/// 卸载所有插件
	void unloadPlugins() override;

	const IPluginList& getPlugins() const override;

protected:
	void execStartPluginFunc(DynLib* lib);
	void execStopPluginFunc(DynLib* lib);

private:
	typedef std::vector<DynLib*> PluginLibList;

	IPluginList mPlugins;
	PluginLibList mPluginLibs;

	DynLibManager* mDynLibManager;
};
