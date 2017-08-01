#include "MenuState.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "GameState.hpp" // Used to switch to
#include "PreState.hpp" // Used to switch to

#include "../Engine/Math/Math.hpp"
#include "../Engine/Math/Vector2.hpp"

MenuState::MenuState(oe::StateManager& manager)
	: oe::State(manager)
{
	mTextureBg.loadFromFile(TEXTURE_MENU);
	mBackground.setTexture(mTextureBg);
	mBackground.setScale(2.0f, 2.0f);

	mScreen.setTexture(getApplication().getTextures().get(GameSingleton::screenTexture));
	mScreen.setTextureRect(sf::IntRect(0, 0, 960, 600));
	mScreen.setPosition(32, 84);

	mPlay.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mQuit.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mSound.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mMusic.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mSoundButton.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mMusicButton.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));
	mName.setTexture(getApplication().getTextures().get(GameSingleton::guiTexture));

	mPlay.setTextureRect(sf::IntRect(0, 384, 288, 96));
	mQuit.setTextureRect(sf::IntRect(480, 96, 288, 96));
	mSound.setTextureRect(sf::IntRect(0, 192, 192, 96));
	mMusic.setTextureRect(sf::IntRect(192, 192, 192, 96));
	mSoundButton.setTextureRect(sf::IntRect((getApplication().getAudio().getSoundVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
	mMusicButton.setTextureRect(sf::IntRect((getApplication().getAudio().getMusicVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
	mName.setTextureRect(sf::IntRect(288, 384, 288, 96));

	mSound.setPosition(sf::Vector2f(560, 580));
	mMusic.setPosition(sf::Vector2f(790, 580));
	mSoundButton.setPosition(sf::Vector2f(615, 375));
	mMusicButton.setPosition(sf::Vector2f(830, 375));
	mPlay.setPosition(150, 300);
	mQuit.setPosition(150, 450);
	mName.setPosition(512 - 144, 120);

	mShadow.setTexture(getApplication().getTextures().get(GameSingleton::shadowTexture));
	mShadow.setTextureRect(sf::IntRect(85, 40, 563 - 85, 333 - 40));
	mShadow.setScale(WINSIZEX / mShadow.getGlobalBounds().width, WINSIZEY / mShadow.getGlobalBounds().height);
}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		static sf::FloatRect cross(30, 80, 40, 40);
		sf::Vector2f mpos((F32)event.mouseButton.x, (F32)event.mouseButton.y);
		if (mPlay.getGlobalBounds().contains(mpos))
		{
			GameSingleton::click();
			pushState<PreState>();
		}
		if (mQuit.getGlobalBounds().contains(mpos) || cross.contains(mpos))
		{
			GameSingleton::playSound(GameSingleton::errorSound);
			getApplication().getWindow().close();
		}
		if (mSoundButton.getGlobalBounds().contains(mpos))
		{
			if (getApplication().getAudio().getSoundVolume() > 0.0f)
			{
				getApplication().getAudio().setSoundVolume(0.0f);
			}
			else
			{
				getApplication().getAudio().setSoundVolume(50.0f);
			}
			mSoundButton.setTextureRect(sf::IntRect((getApplication().getAudio().getSoundVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
			GameSingleton::playSound(GameSingleton::buttonSound);
		}
		else if (mMusicButton.getGlobalBounds().contains(mpos))
		{
			if (getApplication().getAudio().getMusicVolume() > 0.0f)
			{
				getApplication().getAudio().setMusicVolume(0.0f);
			}
			else
			{
				getApplication().getAudio().setMusicVolume(50.0f);
			}
			mMusicButton.setTextureRect(sf::IntRect((getApplication().getAudio().getMusicVolume() > 0.0f) ? 288 : 384, 0, 96, 192));
			GameSingleton::playSound(GameSingleton::buttonSound);
		}
	}
	return false;
}

bool MenuState::update(oe::Time dt)
{
	return false;
}

void MenuState::render(sf::RenderTarget& target)
{
	target.draw(mBackground);

	target.draw(mShadow);

	target.draw(mScreen);

	target.draw(mName);
	target.draw(mPlay);
	target.draw(mQuit);
	target.draw(mSoundButton);
	target.draw(mMusicButton);
	target.draw(mSound);
	target.draw(mMusic);
}
