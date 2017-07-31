#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "../Engine/Core/Map.hpp"
#include "../Engine/System/ParserXml.hpp"

#include "Info.hpp"
#include "Spawner.hpp"
#include "Chest.hpp"
#include "Teleporter.hpp"

#include "RobotMegaKiller.hpp"
#include "RobotKiller.hpp"

class GameMap : public oe::Entity
{
	public:
		GameMap(oe::EntityManager& manager);

		oe::TileId getTileId(const oe::Vector2i& coords);
		void setTileId(const oe::Vector2i& coords, oe::TileId id);

		void load(U32 mapId, const oe::Vector2& spawnPoint, U32 previousMapId);
		U32 getMapId() const;
		U32 getPreviousMapId() const;

		void setSpawnPoint(const oe::Vector2& point);
		const oe::Vector2& getSpawnPoint() const;
		oe::Vector2 getRespawnPoint() const;

		oe::LayerComponent& getLayer();

		void setSize(const oe::Vector2i& size);
		const oe::Vector2i& getSize() const;

		virtual void update(oe::Time dt);

		void setCollision(const oe::Vector2i& coords, bool collide);
		bool collide(const oe::Vector2i& coords);

		Info* getCurrentInfo();

		void openChest(const oe::Vector2i& coords);

		WeaponId getEnemyWeapon() const;
		WeaponId getBossWeapon() const;
		F32 getEnemyBattery() const;
		F32 getBossBattery() const;

		void removeRemovableWalls();

	private:
		void createLayer(const oe::Vector2i& size);
		void readLayer(oe::ParserXml& parser);
		void readObject(oe::ParserXml& parser);
		void readInfo(oe::ParserXml& parser);
		void readChest(oe::ParserXml& parser);
		void readTeleporter(oe::ParserXml& parser);

	private:
		oe::LayerComponent mLayer;
		std::vector<bool> mCollisions;
		std::vector<Info> mInfos;
		std::vector<Spawner> mSpawners;
		std::vector<Chest> mChests;
		std::vector<Teleporter> mTeleporters;
		std::vector<oe::Vector2> mChargers;
		oe::Vector2 mSpawnPoint;
		U32 mMapId;
		U32 mPreviousMapId;
		WeaponId mEnemyWeapon;
		WeaponId mBossWeapon;
		F32 mBossBattery;
		F32 mEnemyBattery;
		Info* mCurrentInfo;
		std::vector<oe::Vector2i> mRemovableWalls;
};

#endif // GAMEMAP_HPP
