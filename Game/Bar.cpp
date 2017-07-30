#include "Bar.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Bar::Bar()
{
	mValue = 0.0f;
	mValueMax = 0.0f;
}

void Bar::setValue(F32 value)
{
	mValue = value;
	if (mValue > mValueMax)
	{
		mValue = mValueMax;
	}
	if (mValue < 0.0f)
	{
		mValue = 0.0f;
	}
	update();
}

F32 Bar::getValue() const
{
	return mValue;
}

void Bar::setValueMax(F32 valueMax)
{
	mValueMax = valueMax;
	update();
}

F32 Bar::getValueMax() const
{
	return mValueMax;
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBack, states);
	target.draw(mBar, states);
}

void Bar::setBarColor(const sf::Color& color)
{
	mBar.setFillColor(color);
}

const sf::Color& Bar::getBarColor() const
{
	return mBar.getFillColor();
}

void Bar::setBackColor(const sf::Color& color)
{
	mBack.setFillColor(color);
}

const sf::Color& Bar::getBackColor() const
{
	return mBack.getFillColor();
}

void Bar::setOutlineColor(const sf::Color& color)
{
	mBack.setOutlineColor(color);
}

const sf::Color& Bar::getOutlineColor() const
{
	return mBack.getOutlineColor();
}

void Bar::setOutlineThickness(F32 thickness)
{
	mBack.setOutlineThickness(thickness);
}

F32 Bar::getOutlineThickness() const
{
	return mBack.getOutlineThickness();
}

void Bar::setSize(F32 width, F32 height)
{
	setSize(sf::Vector2f(width, height));
}

void Bar::setSize(const sf::Vector2f& size)
{
	mBack.setSize(size);
	update();
}

const sf::Vector2f& Bar::getSize() const
{
	return mBack.getSize();
}

void Bar::update()
{
	if (mValueMax > 0.0f)
	{
		const auto& size = mBack.getSize();
		F32 percent = mValue / mValueMax;
		mBar.setSize(sf::Vector2f(percent * size.x, size.y));
	}
}
