#include "Spawner.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

#include "../Engine/Core/EntityManager.hpp"
#include "../Engine/Math/Random.hpp"
#include "RobotMiniKiller.hpp"

Spawner::Spawner(oe::EntityManager&manager, const oe::Vector2& position, U32 count)
	: mManager(manager)
	, mPosition(position)
	, mCount(count)
{
}

void Spawner::spawn()
{
	// Remove invalid
	U32 size = mHandles.size();
	for (U32 i = 0; i < size; )
	{
		if (!mHandles[i].isValid())
		{
			mHandles.erase(mHandles.begin() + i);
			size--;
		}
		else
		{
			i++;
		}
	}

	// Spawn if needed
	if (mHandles.size() < mCount)
	{
		const oe::Vector2 delta = GameSingleton::player->getPosition() - mPosition;
		const F32 d = delta.getLength();
		if (d > SPAWNER_DISTANCE)
		{
			mHandles.push_back(mManager.createEntity<RobotMiniKiller>());
			mHandles.back()->setPosition(getPosition() + oe::Vector2(oe::Random::getDev(0.0f, 100.0f), oe::Random::getDev(0.0f, 100.0f)));
		}
	}
}

void Spawner::setPosition(const oe::Vector2& position)
{
	mPosition = position;
}

const oe::Vector2& Spawner::getPosition() const
{
	return mPosition;
}

void Spawner::update()
{
	spawn();
}
