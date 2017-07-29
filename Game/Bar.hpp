#ifndef BAR_HPP
#define BAR_HPP

#include "../Engine/System/Prerequisites.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class Bar : public sf::Drawable, public sf::Transformable
{
	public:
		Bar();

		void setValue(F32 value);
		F32 getValue() const;

		void setValueMax(F32 valueMax);
		F32 getValueMax() const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

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

	private:
		void update();

	private:
		sf::RectangleShape mBack;
		sf::RectangleShape mBar;
		F32 mValue;
		F32 mValueMax;

};

#endif // BAR_HPP
