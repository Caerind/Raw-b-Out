#ifndef BARCOMPONENT_HPP
#define BARCOMPONENT_HPP

#include "../Engine/Core/RenderableComponent.hpp"

#include "Bar.hpp"


class BarComponent : public oe::RenderableComponent
{
	public:
		BarComponent(oe::Entity& entity, bool attachedToEntity = true);

		void setValue(F32 value);
		F32 getValue() const;

		void setValueMax(F32 valueMax);
		F32 getValueMax() const;

		void setBarColor(const sf::Color& color);
		const sf::Color& getBarColor() const;

		void setBackColor(const sf::Color& color);
		const sf::Color& getBackColor() const;

		void setOutlineColor(const sf::Color& color);
		const sf::Color& getOutlineColor() const;

		void setOutlineThickness(F32 thickness);
		F32 getOutlineThickness() const;

		void setSize(F32 width, F32 height);
		void setSize(const sf::Vector2f& size);
		const sf::Vector2f& getSize() const;

		virtual void render(sf::RenderTarget& target);

	private:
		Bar mBar;
};

#endif // BARCOMPONENT_HPP
