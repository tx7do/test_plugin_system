#include "application.h"
#include "i_plugin.h"
#include "plugin_manager.h"
#include "i_render_system.h"
#include <iostream>

template<>
Application* Singleton<Application>::msSingleton = nullptr;

Application* Application::getSingletonPtr()
{
	return msSingleton;
}

Application& Application::getSingleton()
{
	assert(msSingleton);
	return (*msSingleton);
}

Application::Application()
	: mIsInitialised(false)
{
	mPluginManager = new PluginManager();
	mPluginManager->pluginInstalled = [this](IPlugin* plugin)
	{ onPluginInstalled(plugin); };
	mPluginManager->pluginUninstalled = [this](IPlugin* plugin)
	{ onPluginUninstalled(plugin); };

	std::string pluginFileName{ "plugins.cfg" };
	loadPlugins(pluginFileName);

	mIsInitialised = true;
}

Application::~Application()
{
	delete mPluginManager;
}

void Application::loadPlugins(const std::string& pluginFileName)
{
	//if (pluginFileName.empty()) return;

	mPluginManager->loadPlugin("libogre_plugin", false);
}

static const std::string RenderSystemType{ "RenderSystem" };

void Application::onPluginInstalled(IPlugin* plugin)
{
	if (plugin->getType() == RenderSystemType)
	{
		auto rend = static_cast<IRenderSystem*>(plugin->getObject());
		addRenderSystem(rend);

		std::cout << "RenderSystem installed: " << rend->name() << std::endl;
		std::cout << "RenderSystem count: " << mRenderers.size() << std::endl;
	}
}

void Application::onPluginUninstalled(IPlugin* plugin)
{
	if (plugin->getType() == "RenderSystem")
	{
		auto rend = static_cast<IRenderSystem*>(plugin->getObject());

		// remove from list
		for (auto it = mRenderers.begin(); it != mRenderers.end(); ++it)
		{
			if (*it == rend)
			{
				mRenderers.erase(it);
				break;
			}
		}
	}

	std::cout << "Plugin uninstalled: " << plugin->getType() << " : " << plugin->getName() << " : " << mRenderers.size()
			  << std::endl;
}
