#ifndef POPUP_HPP
#define POPUP_HPP

#include "../Engine/System/Prerequisites.hpp"
#include "../Engine/Application/AudioSystem.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

class PopUp : public sf::Drawable
{
	public:
		PopUp(sf::Texture& screen);

		virtual void handleEvent(const sf::Event& event) = 0;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

		bool isOpen() const;
		bool isExit() const;

	protected:
		sf::Sprite mScreen;
		bool mOpen;
		bool mExit;
};

class RobotPopUp : public PopUp
{
	public:
		RobotPopUp(sf::Texture& screen, sf::Texture& gui, sf::Font& font);

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::Sprite mName;
		sf::Text mNameText;

		sf::Sprite mBattery;
		sf::Sprite mSpeed;
		sf::Sprite mStrength;

		sf::Sprite mBatteryBack;
		sf::Sprite mSpeedBack;
		sf::Sprite mStrengthBack;

		sf::Text mBatteryText;
		sf::Text mSpeedText;
		sf::Text mStrengthText;

		sf::Sprite mBatteryPlus;
		sf::Sprite mSpeedPlus;
		sf::Sprite mStrengthPlus;

		sf::Sprite mBasicValue;
		sf::Sprite mBonusValue;

		sf::Sprite mPointsBack;
		sf::Text mPointsText;

};

class InventoryPopUp : public PopUp
{
	public:
		InventoryPopUp(sf::Texture& screen, sf::Texture& gui, sf::Font& font, sf::Texture& weapons);

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::Vector2f getPosition(U32 weapon);

	protected:
		sf::Text mName;
		sf::Sprite mEquiped;

		std::vector<U32> mPlayerWeapons;
		std::vector<sf::Sprite> mWeaponsSprites;

		U32 mEquipedId;
};

class OptionsPopUp : public PopUp
{
	public:
		OptionsPopUp(sf::Texture& screen, sf::Texture& gui, oe::AudioSystem& manager);

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		oe::AudioSystem& mAudio;
		sf::Sprite mSound;
		sf::Sprite mMusic;
		sf::Sprite mSoundButton;
		sf::Sprite mMusicButton;
		sf::Sprite mResume;
		sf::Sprite mQuit;

};

class MapPopUp : public PopUp
{
	public:
		MapPopUp(sf::Texture& screen, sf::Texture& gui, sf::Texture& head);

		virtual void handleEvent(const sf::Event& event);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		std::vector<sf::Sprite> mSprites;
		sf::Sprite mHead;
};

#endif // POPUP_HPP
