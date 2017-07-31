#include "Info.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

Info::Info()
{
	mString = "";
	mPosition.makeZero();
	mId = 0;
	mVisible = false;
}

void Info::setString(const std::string& str)
{
	mString = str;
}

const std::string& Info::getString() const
{
	return mString;
}

void Info::setPosition(const oe::Vector2& position)
{
	mPosition = position;
}

const oe::Vector2& Info::getPosition() const
{
	return mPosition;
}

void Info::setId(U32 id)
{
	mId = id;
}

U32 Info::getId() const
{
	return mId;
}

bool Info::isVisible() const
{
	return mVisible;
}

bool Info::update()
{
	const oe::Vector2 delta = GameSingleton::player->getPosition() - mPosition;
	const F32 d = delta.getLength();
	if (mVisible && d > GameSingleton::InfoDistance)
	{
		mVisible = false;
	}
	else if (!mVisible && d <= GameSingleton::InfoDistance)
	{
		mVisible = true;
	}
	return mVisible;
}
