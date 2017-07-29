#include "BarComponent.hpp"

BarComponent::BarComponent(oe::Entity& entity, bool attachedToEntity)
	: oe::RenderableComponent(entity, attachedToEntity)
	, mBar()
{
}

void BarComponent::setValue(F32 value)
{
	mBar.setValue(value);
}

F32 BarComponent::getValue() const
{
	return mBar.getValue();
}

void BarComponent::setValueMax(F32 valueMax)
{
	mBar.setValueMax(valueMax);
}

F32 BarComponent::getValueMax() const
{
	return mBar.getValueMax();
}

void BarComponent::setBarColor(const sf::Color& color)
{
	mBar.setBarColor(color);
}

const sf::Color& BarComponent::getBarColor() const
{
	return mBar.getBarColor();
}

void BarComponent::setBackColor(const sf::Color& color)
{
	mBar.setBackColor(color);
}

const sf::Color& BarComponent::getBackColor() const
{
	return mBar.getBackColor();
}

void BarComponent::setOutlineColor(const sf::Color& color)
{
	mBar.setOutlineColor(color);
}

const sf::Color& BarComponent::getOutlineColor() const
{
	return mBar.getOutlineColor();
}

void BarComponent::setOutlineThickness(F32 thickness)
{
	mBar.setOutlineThickness(thickness);
}

F32 BarComponent::getOutlineThickness() const
{
	return mBar.getOutlineThickness();
}

void BarComponent::setSize(F32 width, F32 height)
{
	mBar.setSize(width, height);
	setLocalAABB(oe::Rect(oe::Vector2(0.0f, 0.0f), oe::toOE(getSize())));
}

void BarComponent::setSize(const sf::Vector2f& size)
{
	mBar.setSize(size);
	setLocalAABB(oe::Rect(oe::Vector2(0.0f, 0.0f), oe::toOE(getSize())));
}

const sf::Vector2f& BarComponent::getSize() const
{
	return mBar.getSize();
}

void BarComponent::render(sf::RenderTarget& target)
{
	target.draw(mBar, getGlobalTransform());
}
