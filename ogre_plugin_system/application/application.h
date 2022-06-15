#pragma once

#include <vector>
#include <string>
#include "singleton.h"

class PluginManager;
class IPlugin;
class IRenderSystem;

class Application : public Singleton<Application>
{
public:
	Application();
	~Application();

	static Application& getSingleton();
	static Application* getSingletonPtr();

protected:
	void addRenderSystem(IRenderSystem* newRend)
	{
		mRenderers.push_back(newRend);
	}

protected:
	void loadPlugins(const std::string& pluginFileName = "plugins.cfg");

	void onPluginInstalled(IPlugin* plugin);
	void onPluginUninstalled(IPlugin* plugin);

private:
	PluginManager* mPluginManager;
	bool mIsInitialised;

	typedef std::vector<IRenderSystem*> RenderSystemList;
	RenderSystemList mRenderers;
};
