#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent(oe::Entity& entity, bool attachedToEntity)
	: oe::RenderableComponent(entity, attachedToEntity)
	, mAABB()
{
}

void CollisionComponent::setOrigin(const oe::Vector2& origin)
{
	mOrigin = origin;
	mUpdated = false;
}

const oe::Vector2& CollisionComponent::getOrigin() const
{
	return mOrigin;
}

void CollisionComponent::setSize(const oe::Vector2& size)
{
	mSize = size;
	mUpdated = false;
}

const oe::Vector2& CollisionComponent::getSize() const
{
	return mSize;
}

const oe::Rect& CollisionComponent::getAABB() const
{
	if (!mUpdated)
	{
		oe::Vector2 p = getGlobalPosition() - mOrigin - mSize * 0.5f;
		mAABB = oe::Rect(p.x, p.y, mSize.x, mSize.y);
	}
	return mAABB;
}

void CollisionComponent::onCreate()
{
	mInvalidationSlot.connect(onNodeInvalidation, this, &CollisionComponent::onNodeInvalidated);
}

void CollisionComponent::onNodeInvalidated(const oe::Node* node)
{
	mUpdated = false;
}
