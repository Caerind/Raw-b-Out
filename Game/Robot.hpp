#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/AnimationComponent.hpp"

#include "Weapon.hpp"

class Robot : public oe::Entity
{
	public:
		enum Type
		{
			MiniKiller,
			Killer,
			MegaKiller
		};

		Robot(oe::EntityManager& manager, Type robotType);

		void setBattery(F32 battery);
		F32 getBattery() const;
		bool consumeBattery(F32 amount);

		void setBatteryMax(F32 batteryMax);
		F32 getBatteryMax() const;
		F32 getBatteryMaxWithBonus() const;

		void setSpeed(F32 speed);
		F32 getSpeed() const;
		F32 getSpeedWithBonus() const;

		void setWeapon(WeaponId id);
		WeaponId getWeapon() const;

		Type getRobotType() const;

		bool shoot(const oe::Vector2& pos);

		virtual void update(oe::Time dt);

		virtual bool determineMovement(oe::Vector2& mvt);

		bool tryMove(oe::Time dt, oe::Vector2& mvt);

		void notMoving();

		oe::Animation* getRightAnimationMove();
		oe::Animation* getLeftAnimationMove();
		oe::Animation* getRightAnimationIdle();
		oe::Animation* getLeftAnimationIdle();

	protected:
		oe::AnimationComponent mAnimation;

		oe::Vector2i mCoords;
		oe::Time mWeaponCooldown;

		Weapon mWeapon;
		F32 mBattery;
		F32 mBatteryMax;
		F32	mSpeed;
		Type mRobotType;

		F32 mBatteryBonus;
		F32 mSpeedBonus;
		U32 mStrengthBonus;
};

#endif // ROBOT_HPP
