#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "../Engine/Math/Vector2.hpp"

#include "../Engine/Core/EntityHandle.hpp"

class Spawner
{
	public:
		Spawner(oe::EntityManager& manager, const oe::Vector2& position, U32 count);

		void spawn();

		void setPosition(const oe::Vector2& position);
		const oe::Vector2& getPosition() const;

		void update();

	private:
		oe::EntityManager& mManager;
		oe::Vector2 mPosition;
		U32 mCount;
		std::vector<oe::EntityHandle> mHandles;

};

#endif // SPAWNER_HPP
