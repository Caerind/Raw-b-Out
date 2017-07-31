#ifndef ROBOTPLAYER_HPP
#define ROBOTPLAYER_HPP

#include "Robot.hpp"

#include "../Engine/Core/Components/ActionComponent.hpp"
#include "../Engine/Core/Components/SpriteComponent.hpp"

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
		void updateLook();
		void setLookAt(F32 x);

		void addWeapon(WeaponId id);
		bool hasWeapon(WeaponId id) const;
		std::vector<WeaponId>& getWeapons();

		void charge();
		bool isCharged() const;

		void setColor(const oe::Color& color);
		oe::Color getColor() const;

		void setRespawning(bool respawning);
		bool isRespawning() const;

	private:
		bool determineMovement(oe::Vector2& mvt);

	private:
		oe::ActionComponent mAction;
		oe::SpriteComponent mWheel;
		oe::SpriteComponent mBody;
		oe::SpriteComponent mEyes;
		oe::SpriteComponent mWeaponSprite;

		U32 mLevel;
		U32 mExperience;
		U32 mPoints;

		std::vector<WeaponId> mWeapons;

		bool mRespawning;

};

#endif // ROBOTPLAYER_HPP
