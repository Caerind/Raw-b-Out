#ifndef COLLISIONCOMPONENT_HPP
#define COLLISIONCOMPONENT_HPP

#include "../Engine/Core/RenderableComponent.hpp"

class CollisionComponent : public oe::RenderableComponent
{
	public:
		CollisionComponent(oe::Entity& entity, bool attachedToEntity = true);

		void setOrigin(const oe::Vector2& origin);
		const oe::Vector2& getOrigin() const;

		void setSize(const oe::Vector2& size);
		const oe::Vector2& getSize() const;

		const oe::Rect& getAABB() const;

		virtual void onCreate();

		void onNodeInvalidated(const oe::Node* node);

		OeSlot(oe::Node, onNodeInvalidation, mInvalidationSlot);

	private:
		mutable oe::Rect mAABB;
		oe::Vector2 mOrigin;
		oe::Vector2 mSize;
		mutable bool mUpdated;
};

#endif // COLLISIONCOMPONENT_HPP
