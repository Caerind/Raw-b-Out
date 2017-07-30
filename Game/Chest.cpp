#include "Chest.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

Chest::Chest(const oe::Vector2i& position, WeaponId id)
	: mPosition(position)
	, mWeaponId(id)
	, mOpen(false)
{
}

void Chest::setPosition(const oe::Vector2i& position)
{
	mPosition = position;
}

const oe::Vector2i& Chest::getPosition() const
{
	return mPosition;
}

void Chest::setWeapon(WeaponId id)
{
	mWeaponId = id;
}

WeaponId Chest::getWeapon() const
{
	return mWeaponId;
}

bool Chest::setOpen(bool open)
{
	if (open && !mOpen)
	{
		GameSingleton::map->setTileId(mPosition, TILE_CHEST_OPEN);

		GameSingleton::player->addWeapon(mWeaponId);

		mOpen = open;

		return true;
	}
	else if (!open && mOpen)
	{
		GameSingleton::map->setTileId(mPosition, TILE_CHEST);
		mOpen = open;
	}
	return false;
}

bool Chest::isOpen() const
{
	return mOpen;
}
