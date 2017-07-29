#include "Weapon.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

Weapon::Weapon(WeaponId id)
{
	mId = id;
}

void Weapon::setId(WeaponId id)
{
	mId = id;
}

std::string Weapon::getName() const
{
	return getName(mId);
}

oe::Time Weapon::getCooldown() const
{
	return getCooldown(mId);
}

U32 Weapon::getStrength() const
{
	return getStrength(mId);
}

WeaponId Weapon::getId() const
{
	return mId;
}

Projectile::Type Weapon::getProjType() const
{
	return getProjType(mId);
}

std::string Weapon::getName(WeaponId id)
{
	return GameSingleton::weaponData[id].name;
}

oe::Time Weapon::getCooldown(WeaponId id)
{
	return oe::seconds(GameSingleton::weaponData[id].cool);
}

U32 Weapon::getStrength(WeaponId id)
{
	return GameSingleton::weaponData[id].stre;
}

Projectile::Type Weapon::getProjType(WeaponId id)
{
	return static_cast<Projectile::Type>(GameSingleton::weaponData[id].proj);
}
