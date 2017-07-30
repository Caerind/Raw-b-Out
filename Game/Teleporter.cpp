#include "Teleporter.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"


Teleporter::Teleporter(const oe::Vector2& position, U32 mapId, const oe::Vector2& targetPos)
	: mPosition(position)
	, mTargetPos(targetPos)
	, mMapId(mapId)
{
}

void Teleporter::setPosition(const oe::Vector2& position)
{
	mPosition = position;
}

const oe::Vector2& Teleporter::getPosition() const
{
	return mPosition;
}

void Teleporter::setTargetPos(const oe::Vector2& targetPos)
{
	mTargetPos = targetPos;
}

const oe::Vector2& Teleporter::getTargetPos() const
{
	return mTargetPos;
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
	if (d <= TELEPORTER_DISTANCE)
	{
		for (oe::Entity* entity : GameSingleton::repQuery.getEntities())
		{
			entity->kill();
		}

		GameSingleton::player->setPosition(mTargetPos);
		GameSingleton::player->updateView();

		GameSingleton::map->load(mMapId, mTargetPos);

		return true;
	}	
	return false;
}
