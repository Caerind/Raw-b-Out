#ifndef ROBOTPLAYER_HPP
#define ROBOTPLAYER_HPP

#include "Robot.hpp"

#include "../Engine/Core/Components/ActionComponent.hpp"

class RobotPlayer : public Robot
{
	public:
		RobotPlayer(oe::EntityManager& manager);

		void setLevel(U32 level);
		U32 getLevel() const;
		void gainLevel();

		void setExperience(U32 experience);
		U32 getExperience() const;
		U32 getExperienceMax() const;
		void addExperience(U32 experience);

		void setPoints(U32 points);
		U32 getPoints() const;
		void addPoint();
		void spendPoint();
		bool hasPoints() const;

		void increaseBattery();
		void increaseSpeed();
		void increaseStrength();
		void setBatteryBonus(F32 bonus);
		void setSpeedBonus(F32 bonus);
		void setStrengthBonus(U32 bonus);
		F32 getBatteryBonus() const;
		F32 getSpeedBonus() const;
		U32 getStrengthBonus() const;

		virtual void update(oe::Time dt);

		void shoot();

		void updateView();

		void addWeapon(WeaponId id);

		std::vector<WeaponId>& getWeapons();

	private:
		bool determineMovement(oe::Vector2& mvt);

	private:
		oe::ActionComponent mAction;

		U32 mLevel;
		U32 mExperience;
		U32 mPoints;

		std::vector<WeaponId> mWeapons;

};

#endif // ROBOTPLAYER_HPP
