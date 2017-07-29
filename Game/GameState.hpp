#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

#include "Bar.hpp"

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
};

#endif // GAMESTATE_HPP
