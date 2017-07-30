#ifndef FX_HPP
#define FX_HPP

#include "../Engine/Core/Entity.hpp"
#include "../Engine/Core/Components/ParticleComponent.hpp"

class Fx : public oe::Entity
{
	public:
		enum Type
		{
			PlasmaExplosion,
			UltimeExplosion,
			WallExplosion,
			Charge,
			Level
		};

		Fx(oe::EntityManager& manager, Type type, const oe::Vector2& position);

		virtual void update(oe::Time dt);

	protected:
		oe::ParticleComponent mParticles;
};

#endif // FX_HPP
