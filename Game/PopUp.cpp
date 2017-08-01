#include "PopUp.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "GameConfig.hpp"
#include "GameSingleton.hpp"

PopUp::PopUp(sf::Texture& screen)
{
	mScreen.setTexture(screen);
	mScreen.setPosition(WINSIZEX - 960, WINSIZEY - 20 - 600);
	mOpen = true;
	mExit = false;
}

bool PopUp::isOpen() const
{
	return mOpen;
}

bool PopUp::isExit() const
{
	return mExit;
}

RobotPopUp::RobotPopUp(sf::Texture& screen, sf::Texture& gui, sf::Font& font)
	: PopUp(screen)
{
	mScreen.setTextureRect(sf::IntRect(0, 0, 960, 601));
	sf::Vector2f top = mScreen.getPosition();
	// Text
	auto f = [](sf::Text& t, sf::Font& f) {
		t.setFont(f);
		t.setFillColor(sf::Color(255, 127, 39));
	};
	f(mNameText, font);
	mNameText.setString(GameSingleton::name);
	mNameText.setOrigin(mNameText.getGlobalBounds().width * 0.5f, mNameText.getGlobalBounds().height * 0.5f);
	mNameText.setPosition(310.0f, 230.0f);
	f(mBatteryText, font);
	mBatteryText.setString(oe::toString((U32)GameSingleton::player->getBatteryMax()) + " + " + oe::toString((U32)GameSingleton::player->getBatteryBonus()));
	mBatteryText.setOrigin(mBatteryText.getGlobalBounds().width * 0.5f, mBatteryText.getGlobalBounds().height * 0.5f);
	mBatteryText.setPosition(630.0f, 420.0f);
	f(mSpeedText, font);
	mSpeedText.setString(oe::toString((U32)GameSingleton::player->getSpeed()) + " + " + oe::toString((U32)GameSingleton::player->getSpeedBonus()));
	mSpeedText.setOrigin(mSpeedText.getGlobalBounds().width * 0.5f, mSpeedText.getGlobalBounds().height * 0.5f);
	mSpeedText.setPosition(630.0f, 525.0f);
	f(mStrengthText, font);
	mStrengthText.setString(oe::toString(GameSingleton::weaponData[GameSingleton::player->getWeapon()].stre) + " + " + oe::toString(GameSingleton::player->getStrengthBonus()));
	mStrengthText.setOrigin(mStrengthText.getGlobalBounds().width * 0.5f, mStrengthText.getGlobalBounds().height * 0.5f);
	mStrengthText.setPosition(630.0f, 630.0f);
	f(mPointsText, font);
	mPointsText.setString(oe::toString(GameSingleton::player->getPoints()));
	mPointsText.setOrigin(mPointsText.getGlobalBounds().width * 0.5f, mPointsText.getGlobalBounds().height * 0.5f);
	mPointsText.setPosition(910.0f, 230.0f);

	mName.setTexture(gui);
	mBattery.setTexture(gui);
	mBatteryBack.setTexture(gui);
	mBatteryPlus.setTexture(gui);
	mSpeed.setTexture(gui);
	mSpeedBack.setTexture(gui);
	mSpeedPlus.setTexture(gui);
	mStrength.setTexture(gui);
	mStrengthBack.setTexture(gui);
	mStrengthPlus.setTexture(gui);
	mBasicValue.setTexture(gui);
	mBonusValue.setTexture(gui);
	mPointsBack.setTexture(gui);

	mName.setTextureRect(sf::IntRect(769, 288, 287, 96));
	mBattery.setTextureRect(sf::IntRect(768, 0, 288, 96));
	mBatteryBack.setTextureRect(sf::IntRect(769, 288, 287, 96));
	mBatteryPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
	mSpeed.setTextureRect(sf::IntRect(768, 96, 288, 96));
	mSpeedBack.setTextureRect(sf::IntRect(769, 288, 287, 96));
	mSpeedPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
	mStrength.setTextureRect(sf::IntRect(768, 192, 288, 96));
	mStrengthBack.setTextureRect(sf::IntRect(769, 288, 287, 96));
	mStrengthPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
	mBasicValue.setTextureRect(sf::IntRect(0, 288, 96, 96));
	mBonusValue.setTextureRect(sf::IntRect(96, 288, 96, 96));
	mPointsBack.setTextureRect(sf::IntRect(576, 288, 96, 96));

	mName.setPosition(top + sf::Vector2f(110.0f, 35.0f));
	mBattery.setPosition(top + sf::Vector2f(50.0f, 220.0f));
	mBatteryBack.setPosition(top + sf::Vector2f(430.0f, 220.0f));
	mBatteryPlus.setPosition(top + sf::Vector2f(800.0f, 220.0f));
	mSpeed.setPosition(top + sf::Vector2f(50.0f, 325.0f));
	mSpeedBack.setPosition(top + sf::Vector2f(430.0f, 325.0f));
	mSpeedPlus.setPosition(top + sf::Vector2f(800.0f, 325.0f));
	mStrength.setPosition(top + sf::Vector2f(50.0f, 430.0f));
	mStrengthBack.setPosition(top + sf::Vector2f(430.0f, 430.0f));
	mStrengthPlus.setPosition(top + sf::Vector2f(800.0f, 430.0f));
	mBasicValue.setPosition(top + sf::Vector2f(450.0f, 100.0f));
	mBonusValue.setPosition(top + sf::Vector2f(610.0f, 100.0f));
	mPointsBack.setPosition(top + sf::Vector2f(800.0f, 35.0f));
}

void RobotPopUp::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && GameSingleton::player->hasPoints())
	{
		GameSingleton::click();
		sf::Vector2f pos((F32)event.mouseButton.x, (F32)event.mouseButton.y);
		if (mBatteryPlus.getGlobalBounds().contains(pos))
		{
			GameSingleton::player->increaseBattery();
			mBatteryText.setString(oe::toString((U32)GameSingleton::player->getBatteryMax()) + " + " + oe::toString((U32)GameSingleton::player->getBatteryBonus()));
			mBatteryText.setOrigin(mBatteryText.getGlobalBounds().width * 0.5f, mBatteryText.getGlobalBounds().height * 0.5f);
			mPointsText.setString(oe::toString(GameSingleton::player->getPoints()));
			mPointsText.setOrigin(mPointsText.getGlobalBounds().width * 0.5f, mPointsText.getGlobalBounds().height * 0.5f);
			mBatteryPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mSpeedPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mStrengthPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
		}
		else if (mSpeedPlus.getGlobalBounds().contains(pos))
		{
			GameSingleton::player->increaseSpeed();
			mSpeedText.setString(oe::toString((U32)GameSingleton::player->getSpeed()) + " + " + oe::toString((U32)GameSingleton::player->getSpeedBonus()));
			mSpeedText.setOrigin(mSpeedText.getGlobalBounds().width * 0.5f, mSpeedText.getGlobalBounds().height * 0.5f);
			mPointsText.setString(oe::toString(GameSingleton::player->getPoints()));
			mPointsText.setOrigin(mPointsText.getGlobalBounds().width * 0.5f, mPointsText.getGlobalBounds().height * 0.5f);
			mBatteryPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mSpeedPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mStrengthPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
		}
		else if (mStrengthPlus.getGlobalBounds().contains(pos))
		{
			GameSingleton::player->increaseStrength();
			mStrengthText.setString(oe::toString(GameSingleton::weaponData[GameSingleton::player->getWeapon()].stre) + " + " + oe::toString(GameSingleton::player->getStrengthBonus()));
			mStrengthText.setOrigin(mStrengthText.getGlobalBounds().width * 0.5f, mStrengthText.getGlobalBounds().height * 0.5f);
			mPointsText.setString(oe::toString(GameSingleton::player->getPoints()));
			mPointsText.setOrigin(mPointsText.getGlobalBounds().width * 0.5f, mPointsText.getGlobalBounds().height * 0.5f);
			mBatteryPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mSpeedPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
			mStrengthPlus.setTextureRect(sf::IntRect((GameSingleton::player->hasPoints()) ? 672 : 576, 192, 96, 96));
		}
	}
}

void RobotPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mScreen);

	target.draw(mName);
	target.draw(mNameText);

	target.draw(mBattery);
	target.draw(mSpeed);
	target.draw(mStrength);

	target.draw(mBatteryBack);
	target.draw(mSpeedBack);
	target.draw(mStrengthBack);

	target.draw(mBatteryText);
	target.draw(mSpeedText);
	target.draw(mStrengthText);

	target.draw(mBatteryPlus);
	target.draw(mSpeedPlus);
	target.draw(mStrengthPlus);

	target.draw(mBasicValue);
	target.draw(mBonusValue);

	target.draw(mPointsBack);
	target.draw(mPointsText);
}

InventoryPopUp::InventoryPopUp(sf::Texture& screen, sf::Texture& gui, sf::Font& font, sf::Texture& weapons)
	: PopUp(screen)
{
	mScreen.setTextureRect(sf::IntRect(0, 601, 960, 601));

	auto& v = GameSingleton::player->getWeapons();
	for (U32 i = 0; i < v.size(); i++)
	{
		U32 id = (U32)v[i];
		if (id != 0 && id != 50)
		{
			mPlayerWeapons.push_back(id);
			mWeaponsSprites.push_back(sf::Sprite(weapons));
			mWeaponsSprites.back().setTextureRect(GameSingleton::getTextureRectFromWeapon((WeaponId)id));
			mWeaponsSprites.back().setPosition(getPosition(id) + sf::Vector2f(6.0f, 6.0f));
		}
	}

	mName.setFont(font);
	mName.setFillColor(sf::Color(255, 127, 39));
	mName.setPosition(540, 600);
	mName.setString("");
	mName.setOrigin(mName.getGlobalBounds().width * 0.5f, mName.getGlobalBounds().height * 0.5f);

	mEquipedId = GameSingleton::player->getWeapon();
	mEquiped.setTexture(gui);
	mEquiped.setTextureRect(sf::IntRect(454, 300, 64, 64));
	mEquiped.setPosition(getPosition(mEquipedId) + sf::Vector2f(6.f, 6.f));

	if (mEquipedId != 0)
	{
		mName.setString(GameSingleton::weaponData[mEquipedId].name);
		mName.setOrigin(mName.getGlobalBounds().width * 0.5f, mName.getGlobalBounds().height * 0.5f);
	}
}

void InventoryPopUp::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f pos((F32)event.mouseButton.x, (F32)event.mouseButton.y);
		for (U32 i = 0; i < mWeaponsSprites.size(); i++)
		{
			if (mWeaponsSprites[i].getGlobalBounds().contains(pos))
			{
				U32 id = mPlayerWeapons[i];

				mEquipedId = id;
				GameSingleton::player->setWeapon((WeaponId)mEquipedId);
				mEquiped.setPosition(getPosition(mEquipedId) + sf::Vector2f(6.f, 6.f));
				GameSingleton::click();

				mName.setString(GameSingleton::weaponData[id].name);
				mName.setOrigin(mName.getGlobalBounds().width * 0.5f, mName.getGlobalBounds().height * 0.5f);
			}
		}
	}
}

void InventoryPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mScreen);

	for (U32 i = 0; i < mWeaponsSprites.size(); i++)
	{
		target.draw(mWeaponsSprites[i]);
	}

	target.draw(mName);
	target.draw(mEquiped);
}

sf::Vector2f InventoryPopUp::getPosition(U32 weapon)
{
	if (weapon == 0 || weapon >= 50)
	{
		return sf::Vector2f(-100.0f, -100.0f);
	}

	weapon--;

	U32 x = ((U32)mScreen.getPosition().x) + 191 + 76 * (weapon % 10);
	U32 y = ((U32)mScreen.getPosition().y) + 9 + 76 * (weapon / 10);

	return sf::Vector2f((F32)x, (F32)y);
}

OptionsPopUp::OptionsPopUp(sf::Texture& screen, sf::Texture& gui, oe::AudioSystem& manager)
	: PopUp(screen)
	, mAudio(manager)
{
	mScreen.setTextureRect(sf::IntRect(0, 0, 960, 601));
	sf::Vector2f top = mScreen.getPosition();

	mSound.setTexture(gui);
	mMusic.setTexture(gui);
	mSoundButton.setTexture(gui);
	mMusicButton.setTexture(gui);
	mResume.setTexture(gui);
	mQuit.setTexture(gui);

	mSound.setTextureRect(sf::IntRect(0, 192, 192, 96));
	mMusic.setTextureRect(sf::IntRect(192, 192, 192, 96));
	mSoundButton.setTextureRect(sf::IntRect((mAudio.getSoundVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
	mMusicButton.setTextureRect(sf::IntRect((mAudio.getMusicVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
	mResume.setTextureRect(sf::IntRect(480, 0, 288, 96));
	mQuit.setTextureRect(sf::IntRect(480, 96, 288, 96));

	mSound.setPosition(top + sf::Vector2f(60, 330));
	mMusic.setPosition(top + sf::Vector2f(290, 330));
	mSoundButton.setPosition(top + sf::Vector2f(115, 125));
	mMusicButton.setPosition(top + sf::Vector2f(330, 125));
	mResume.setPosition(top + sf::Vector2f(560, 175));
	mQuit.setPosition(top + sf::Vector2f(560, 320));
}

void OptionsPopUp::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f pos((F32)event.mouseButton.x, (F32)event.mouseButton.y);
		if (mSoundButton.getGlobalBounds().contains(pos))
		{
			if (mAudio.getSoundVolume() > 0.0f)
			{
				mAudio.setSoundVolume(0.0f);
			}
			else
			{
				mAudio.setSoundVolume(50.0f);
			}
			mSoundButton.setTextureRect(sf::IntRect((mAudio.getSoundVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
			GameSingleton::playSound(GameSingleton::buttonSound);
		}
		else if (mMusicButton.getGlobalBounds().contains(pos))
		{
			if (mAudio.getMusicVolume() > 0.0f)
			{
				mAudio.setMusicVolume(0.0f);
			}
			else
			{
				mAudio.setMusicVolume(50.0f);
			}
			mMusicButton.setTextureRect(sf::IntRect((mAudio.getMusicVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
			GameSingleton::playSound(GameSingleton::buttonSound);
		}
		else if (mResume.getGlobalBounds().contains(pos))
		{
			mOpen = false;
			GameSingleton::click();
		}
		else if (mQuit.getGlobalBounds().contains(pos))
		{
			mExit = true;
			GameSingleton::click();
		}
	}
}

void OptionsPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mScreen);
	target.draw(mSound);
	target.draw(mMusic);
	target.draw(mSoundButton);
	target.draw(mMusicButton);
	target.draw(mResume);
	target.draw(mQuit);
}

MapPopUp::MapPopUp(sf::Texture& screen, sf::Texture& gui, sf::Texture& head)
	: PopUp(screen)
{
	mScreen.setTextureRect(sf::IntRect(0, 0, 960, 601));
	sf::Vector2f top = mScreen.getPosition();

	// TODO : Load Map PopUp
	U32 size = GameSingleton::visited.size();
	for (U32 i = 0; i < size; i++)
	{
		mSprites.push_back(sf::Sprite(gui));
		mSprites.back().setTextureRect(sf::IntRect(672, 288, 64,64));
		sf::Vector2f p;
		switch (GameSingleton::visited[i])
		{
		case 0: p = sf::Vector2f(0,0); break;
		case 1: p = sf::Vector2f(64,32); break;
		case 2: p = sf::Vector2f(0,64); break;
		case 3: p = sf::Vector2f(128,0); break;
		case 4: p = sf::Vector2f(128,64); break;
		case 5: p = sf::Vector2f(160,128); break;
		case 6: p = sf::Vector2f(192+32,128+32); break;
		case 7: p = sf::Vector2f(192+32,64+32); break;
		case 8: p = sf::Vector2f(256+32,64); break;
		case 9: p = sf::Vector2f(256+32,128); break;
		case 10: p = sf::Vector2f(192,192+32); break;
		case 11: p = sf::Vector2f(128,192+64); break;
		case 12: p = sf::Vector2f(64,192 + 64); break;
		case 13: p = sf::Vector2f(64,128 + 64); break;
		case 14: p = sf::Vector2f(0,128 + 64); break;
		case 15: p = sf::Vector2f(0,192 + 64); break;
		case 16: p = sf::Vector2f(0 + 32, 256 + 64); break;
		case 17: p = sf::Vector2f(64 + 32, 256 + 64); break;
		case 18: p = sf::Vector2f(128 + 32, 256 + 64); break;
		case 19: p = sf::Vector2f(192 + 32, 256 + 64); break;
		case 20: p = sf::Vector2f(256 + 32, 256 + 64); break;
		case 21: p = sf::Vector2f(256 + 32, 192 + 64); break;
		default: break;
		}
		p += top + sf::Vector2f(200, 100);
		mSprites.back().setPosition(p);
	}

	mHead.setTexture(head);
	sf::Vector2f p;
	switch (GameSingleton::map->getMapId())
	{
		case 0: p = sf::Vector2f(0, 0); break;
		case 1: p = sf::Vector2f(64, 32); break;
		case 2: p = sf::Vector2f(0, 64); break;
		case 3: p = sf::Vector2f(128, 0); break;
		case 4: p = sf::Vector2f(128, 64); break;
		case 5: p = sf::Vector2f(160, 128); break;
		case 6: p = sf::Vector2f(192 + 32, 128 + 32); break;
		case 7: p = sf::Vector2f(192 + 32, 64 + 32); break;
		case 8: p = sf::Vector2f(256 + 32, 64); break;
		case 9: p = sf::Vector2f(256 + 32, 128); break;
		case 10: p = sf::Vector2f(192, 192 + 32); break;
		case 11: p = sf::Vector2f(128, 192 + 64); break;
		case 12: p = sf::Vector2f(64, 192 + 64); break;
		case 13: p = sf::Vector2f(64, 128 + 64); break;
		case 14: p = sf::Vector2f(0, 128 + 64); break;
		case 15: p = sf::Vector2f(0, 192 + 64); break;
		case 16: p = sf::Vector2f(0 + 32, 256 + 64); break;
		case 17: p = sf::Vector2f(64 + 32, 256 + 64); break;
		case 18: p = sf::Vector2f(128 + 32, 256 + 64); break;
		case 19: p = sf::Vector2f(192 + 32, 256 + 64); break;
		case 20: p = sf::Vector2f(256 + 32, 256 + 64); break;
		case 21: p = sf::Vector2f(256 + 32, 192 + 64); break;
		default: break;
	}
	p += top + sf::Vector2f(210, 110);
	mHead.setPosition(p);
}

void MapPopUp::handleEvent(const sf::Event& event)
{
	// Nothing
}

void MapPopUp::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mScreen);
	for (U32 i = 0; i < mSprites.size(); i++)
	{
		target.draw(mSprites[i]);
	}
	target.draw(mHead);
}
