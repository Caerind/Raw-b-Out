#include "Teleporter.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"
#include "GameState.hpp"


Teleporter::Teleporter(const oe::Vector2& position, U32 mapId, U32 currentId, bool activated)
	: mPosition(position)
	, mMapId(mapId)
	, mCurrentId(currentId)
	, mActivated(activated)
{
	if (mActivated)
	{
		GameSingleton::player->setPosition(position);
		GameSingleton::player->updateView();
		GameSingleton::map->setSpawnPoint(position);
	}
}

void Teleporter::setPosition(const oe::Vector2& position)
{
	mPosition = position;
}

const oe::Vector2& Teleporter::getPosition() const
{
	return mPosition;
}

void Teleporter::setMapId(U32 mapId)
{
	mMapId = mapId;
}

U32 Teleporter::getMapId() const
{
	return mMapId;
}

bool Teleporter::update()
{
	const oe::Vector2 delta = GameSingleton::player->getPosition() - mPosition;
	const F32 d = delta.getLength();

	if (mActivated && d >= GameSingleton::TeleporterLostDistance)
	{
		mActivated = false;
	}
	else if (d <= GameSingleton::TeleporterDistance && !mActivated)
	{
		if (GameSingleton::player->isRespawning())
		{
			mActivated = true;
			GameSingleton::player->setRespawning(false);
		}
		else
		{
			GameSingleton::playSound(GameSingleton::teleportSound);

			if (!GameSingleton::playingMainMusic)
			{
				GameSingleton::playMain();
			}

			for (oe::Entity* entity : GameSingleton::repQuery.getEntities())
			{
				entity->kill();
			}

			GameSingleton::player->setPosition(mPosition);
			GameSingleton::player->updateView();

			GameSingleton::player->charge();

			GameSingleton::map->load(mMapId, mPosition, mCurrentId);

			GameState::save();

			GameSingleton::enemyFocus = 0;

			return true;
		}
	}
	return false;
}

void Teleporter::setActivated(bool activated)
{
	mActivated = activated;
}

bool Teleporter::isActivated() const
{
	return mActivated;
}
