#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Engine/Application/StateManager.hpp"
#include "../Engine/Core/World.hpp"

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
		void moveView(oe::Time dt);

		void initMap();
		oe::Vector2i getCoordsZone(U32 zone);

		oe::Vector2i getMouseCoords();
		void moveView(const sf::Event& event);

	private:
		oe::World mWorld;
		oe::Clock mClock;
};

#endif // GAMESTATE_HPP
