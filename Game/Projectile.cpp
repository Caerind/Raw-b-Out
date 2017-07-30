#include "Projectile.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

Projectile::Projectile(oe::EntityManager& manager, Type projType, const oe::Vector2& position, const oe::Vector2& direction, U32 strength, U32 stricker)
	: oe::Entity(manager)
	, mSprite(*this)
	, mStrength(strength / 5) // Used for more active combat
	, mStricker(stricker)
	, mProjType(projType)
	, mDirection(direction)
{
	setPosition(position);
	setPositionZ(5.0f);

	mSprite.setTexture(GameSingleton::projectilesTexture);
	mSprite.setPosition(-16.0f, -16.0f);

	switch (mProjType)
	{
		case None: mSprite.setTextureRect(sf::IntRect(0, 0, 1, 1)); break;
		case Ammo: mSprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); break;
		case Plasma: mSprite.setTextureRect(sf::IntRect(32, 0, 32, 32)); break;
		case Laser: mSprite.setTextureRect(sf::IntRect(64, 0, 32, 32)); rotate(mDirection.getPolarAngle()); break;
		case Ultime: mSprite.setTextureRect(sf::IntRect(92, 0, 32, 32)); rotate(mDirection.getPolarAngle()); break;
	}
}

Projectile::Type Projectile::getProjType() const
{
	return mProjType;
}

void Projectile::update(oe::Time dt)
{
	oe::Vector2 mvt(mDirection);
	mvt.setLength(dt.asSeconds() * 500.0f); // Proj speed
	oe::Vector2 nextPos = getPosition() + mvt;
	oe::Vector2i coords = oe::MapUtility::worldToCoords(nextPos, oe::MapUtility::Orthogonal, oe::Vector2i(MAPTILESIZEX, MAPTILESIZEY));

	if (mProjType == Type::Plasma)
	{
		rotate(400.f * dt.asSeconds());
	}

	// Proj AABB
	//oe::DebugDraw::drawRect(getAABB());
	
	bool collision = false;
	if (coords != mCoords)
	{
		if (GameSingleton::map->collide(coords))
		{
			collision = true;
		}
		else
		{
			mCoords = coords;
		}
	}

	if (!collision)
	{
		setPosition(nextPos);
	}
	else
	{
		kill();
	}

	// TODO : Plasma & Laser Effect

	mElapsed += dt;
	const oe::Rect& r = getAABB();
	for (Entity* entity : GameSingleton::rpQuery.getEntities()) // If need to optimise, we can use only robots
	{
		if (entity->getAABB().intersects(r))
		{
			Robot* robot = entity->getAs<Robot>();
			if (robot != nullptr && ((robot->getId() != mStricker) || (robot->getId() == mStricker && mElapsed > oe::seconds(0.4f))))
			{
				if (robot->consumeBattery((F32)mStrength) && mStricker == GameSingleton::player->getId())
				{
					U32 amountExp = 0;
					switch (robot->getRobotType())
					{
						case Robot::MiniKiller: amountExp = 10; break;
						case Robot::Killer: amountExp = 100; break;
						case Robot::MegaKiller: amountExp = 5000; break;
						default: break;
					}
					GameSingleton::player->addExperience(amountExp);
				}
				kill();
			}
			else
			{
				Projectile* projectile = entity->getAs<Projectile>();
				if (projectile != nullptr && projectile != this)
				{
					projectile->kill();
					kill();
				}
			}
		}
	}
}
