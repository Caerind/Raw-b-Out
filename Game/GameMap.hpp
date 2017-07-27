#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "../Engine/Core/Map.hpp"

class GameMap : public oe::Map
{
	public:
		GameMap(oe::EntityManager& manager);

		void setTileId(const oe::Vector2& worldPos, oe::TileId tile);
		void setTileId(const oe::Vector2i& coords, oe::TileId tile);

		oe::LayerComponent& getLayer();

	private:
		oe::LayerComponent* mLayer;
};

#endif // GAMEMAP_HPP
