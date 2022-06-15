#pragma once

class IRenderSystem
{
public:
	IRenderSystem() = default;
	virtual ~IRenderSystem() = default;

	virtual std::string name() const = 0;
};
