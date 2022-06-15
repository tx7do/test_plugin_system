#include "render_plugin.h"
#include "i_render_system.h"
#include <string>

class D3D11RenderSystem final : public IRenderSystem
{
public:
	D3D11RenderSystem() = default;
	~D3D11RenderSystem() override = default;

	std::string name() const final
	{
		return "D3D11 RenderSystem";
	}
};

D3D11Plugin::D3D11Plugin()
	: mRenderSystem(nullptr)
{
}

const std::string& D3D11Plugin::getType() const
{
	static const std::string sPluginType{ "RenderSystem" };
	return sPluginType;
}

const std::string& D3D11Plugin::getName() const
{
	static const std::string sPluginName{ "D3D11 RenderSystem" };
	return sPluginName;
}

void D3D11Plugin::install()
{
	mRenderSystem = new D3D11RenderSystem();
	//Root::getSingleton().addRenderSystem(mRenderSystem);
}

void D3D11Plugin::initialise()
{
	// nothing to do
}

void D3D11Plugin::shutdown()
{
	// nothing to do
}

void D3D11Plugin::uninstall()
{
	delete mRenderSystem;
	mRenderSystem = nullptr;
}

void* D3D11Plugin::getObject() const
{
	return mRenderSystem;
}
