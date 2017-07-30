#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "../Engine/Core/Entity.hpp"

#include "../Engine/Core/Components/SpriteComponent.hpp"

class Projectile : public oe::Entity
{
	public:
		enum Type
		{
			None = 0,
			Ammo = 1,
			Plasma = 2,
			Laser = 3,
			Ultime = 4
		};

		Projectile(oe::EntityManager& manager, Type projType, const oe::Vector2& position, const oe::Vector2& direction, U32 strength, U32 stricker);

		Type getProjType() const;

		virtual void update(oe::Time dt);

		void explode(U32 ignoreId = 0);

	protected:
		oe::SpriteComponent mSprite;
		oe::Vector2 mDirection;
		oe::Vector2i mCoords;
		oe::Time mElapsed;
		U32 mStrength;
		U32 mStricker;
		Type mProjType;
};

#endif // PROJECTILE_HPP
