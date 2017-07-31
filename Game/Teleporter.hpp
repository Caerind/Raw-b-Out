#ifndef TELEPORTER_HPP
#define TELEPORTER_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "../Engine/Math/Vector2.hpp"

class Teleporter
{
	public:
		Teleporter(const oe::Vector2& position, U32 mapId, U32 currentId, bool activated);

		void setPosition(const oe::Vector2& position);
		const oe::Vector2& getPosition() const;

		void setMapId(U32 mapId);
		U32 getMapId() const;

		bool update();

		void setActivated(bool activated);
		bool isActivated() const;

	private:
		oe::Vector2 mPosition;
		U32 mMapId;
		U32 mCurrentId;
		bool mActivated;
};

#endif // TELEPORTER_HPP
