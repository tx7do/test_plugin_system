#pragma once

#include "i_plugin.h"
#include <string>

class D3D11RenderSystem;

class D3D11Plugin final : public IPlugin
{
public:
	D3D11Plugin();

	const std::string& getType() const override;

	const std::string& getName() const override;

	void* getObject() const override;

	void install() override;

	void initialise() override;

	void shutdown() override;

	void uninstall() override;

protected:
	D3D11RenderSystem* mRenderSystem;
};
