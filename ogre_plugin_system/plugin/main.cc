#include "render_plugin.h"

static D3D11Plugin* plugin;


extern "C"
void dllStartPlugin(IPluginManager* pluginManager) noexcept(false)
{
	plugin = new D3D11Plugin();
	pluginManager->installPlugin(plugin, true);
}

extern "C"
void dllStopPlugin(IPluginManager* pluginManager)
{
	pluginManager->uninstallPlugin(plugin, true);
	delete plugin;
}
