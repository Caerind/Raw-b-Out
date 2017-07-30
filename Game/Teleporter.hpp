#ifndef TELEPORTER_HPP
#define TELEPORTER_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "../Engine/Math/Vector2.hpp"

class Teleporter
{
	public:
		Teleporter(const oe::Vector2& position, U32 mapId, const oe::Vector2& targetPos);

		void setPosition(const oe::Vector2& position);
		const oe::Vector2& getPosition() const;

		void setTargetPos(const oe::Vector2& targetPos);
		const oe::Vector2& getTargetPos() const;

		void setMapId(U32 mapId);
		U32 getMapId() const;

		bool update();

	private:
		oe::Vector2 mPosition;
		oe::Vector2 mTargetPos;
		U32 mMapId;
};

#endif // TELEPORTER_HPP
