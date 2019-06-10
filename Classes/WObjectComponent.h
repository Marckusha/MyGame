#pragma once
#include "WorldComponent.h"

class WObjectComponent : public WorldComponent {
public:
	WObjectComponent()
		: WorldComponent()
	{}

	virtual void eventTo() override;

private:
};