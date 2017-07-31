#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Engine/Application/StateManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class MenuState : public oe::State
{
	public:
		MenuState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		sf::Texture mTextureBg;
		sf::Sprite mBackground;
		sf::Sprite mScreen;
		sf::Sprite mPlay;
		sf::Sprite mQuit;
		sf::Sprite mSoundButton;
		sf::Sprite mMusicButton;
		sf::Sprite mSound;
		sf::Sprite mMusic;
		sf::Sprite mName;
		sf::Sprite mShadow;
};

#endif // MENUSTATE_HPP
