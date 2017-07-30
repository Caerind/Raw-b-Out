#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

#include "Bar.hpp"
#include "PopUp.hpp"

class GameState : public oe::State
{
	public:
		GameState(oe::StateManager& manager);

		bool handleEvent(const sf::Event& event);
		bool update(oe::Time dt);
		void render(sf::RenderTarget& target);

	private:
		inline oe::Window& getWindow();
		inline oe::View& getView();
		void zoomView(const sf::Event& event);
		void popUpEvent(const sf::Event& event);

		void load();
		void save();

	private:
		oe::World mWorld;
		oe::Time mDuration;
		oe::ImGuiProfiler mProfiler;
		oe::ImGuiDataViewer mDataViewer;

		sf::Text mInfoText;
		U32 mCurrentInfo;

		Bar mBarPlayerLevel;
		Bar mBarPlayerBattery;
		sf::Text mPlayerLevelText;
		Bar mBarPlayerCooldown;

		sf::Sprite mButtonR;
		sf::Sprite mButtonI;
		sf::Sprite mButtonO;
		U32 mCurrentPopUp;
		PopUp* mPopUp;

};

#endif // GAMESTATE_HPP
