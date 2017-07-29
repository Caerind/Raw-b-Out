#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "Projectile.hpp"

using WeaponId = U32;

class Weapon
{
	public:
		Weapon(WeaponId id = 0);

		void setId(WeaponId id);

		std::string getName() const;
		oe::Time getCooldown() const;
		U32 getStrength() const;
		WeaponId getId() const;
		Projectile::Type getProjType() const;

		static std::string getName(WeaponId id);
		static oe::Time getCooldown(WeaponId id);
		static U32 getStrength(WeaponId id);
		static Projectile::Type getProjType(WeaponId id);

	private:
		WeaponId mId;
};

#endif // WEAPON_HPP
