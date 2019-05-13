#include "ControllerComponent.h"

USING_NS_CC;

ControllerComponent::ControllerComponent()
	: _controllSprite(nullptr)
{}

ControllerComponent::ControllerComponent(Sprite* sprite)
	: _controllSprite(sprite)
{}