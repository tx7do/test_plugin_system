#pragma once

#include "i_plugin.h"

class PluginA final : public IPlugin
{
public:
	PluginA() = default;
	~PluginA() final = default;
	std::string name() const final;
};

class PluginB final : public IPlugin
{
public:
	PluginB() = default;
	~PluginB() final = default;
	std::string name() const final;
};

class PluginC final : public IPlugin
{
public:
	PluginC() = default;
	~PluginC() final = default;
	std::string name() const final;
};
