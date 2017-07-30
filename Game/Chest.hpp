#ifndef CHEST_HPP
#define CHEST_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "../Engine/Math/Vector2.hpp"

#include "Weapon.hpp"

class Chest
{
	public:
		Chest(const oe::Vector2i& position, WeaponId id);

		void setPosition(const oe::Vector2i& position);
		const oe::Vector2i& getPosition() const;

		void setWeapon(WeaponId id);
		WeaponId getWeapon() const;

		bool setOpen(bool open);
		bool isOpen() const;

	private:
		oe::Vector2i mPosition;
		WeaponId mWeaponId;
		bool mOpen;
};

#endif // CHARGER_HPP
