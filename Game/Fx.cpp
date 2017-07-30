#include "Fx.hpp"

#include "GameSingleton.hpp"
#include "GameConfig.hpp"

Fx::Fx(oe::EntityManager& manager, Type type, const oe::Vector2& position)
	: oe::Entity(manager)
	, mParticles(*this)
{
	setPosition(position);

	mParticles.setTexture(GameSingleton::particleTexture);
	mParticles.addTextureRect(0, 0, 6, 6);

	switch (type)
	{
		case PlasmaExplosion: 
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 300.f, 400.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(1.5f, 1.5f), oe::Vector2(0.25f, 0.25f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.4f), oe::seconds(0.5f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distribution<oe::Color>([]() -> oe::Color
			{
				F32 r = 20 * oe::Random::get(0.5f, 1.0f);
				F32 g = 60 * oe::Random::get(0.5f, 1.5f);
				F32 b = 20 * oe::Random::get(0.5f, 1.0f);
				return oe::Color((U8)r, (U8)g, (U8)b);
			}));
			mParticles.emitParticles(50);
			setPositionZ(10);
			break;
		case UltimeExplosion:
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 300.f, 400.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(1.5f, 1.5f), oe::Vector2(0.25f, 0.25f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.4f), oe::seconds(0.5f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distribution<oe::Color>([]() -> oe::Color
			{
				F32 r = 10 * oe::Random::get(0.5f, 1.0f);
				F32 g = 10 * oe::Random::get(0.5f, 1.0f);
				F32 b = 200 * oe::Random::get(0.8f, 1.2f);
				return oe::Color((U8)r, (U8)g, (U8)b);
			}));
			mParticles.emitParticles(50);
			setPositionZ(10);
			break;
		case WallExplosion: 
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 50.f, 100.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(2.f, 2.f), oe::Vector2(0.4f, 0.4f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.3f), oe::seconds(0.5f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distribution<oe::Color>([]() -> oe::Color
			{
				F32 r = 60 * oe::Random::get(0.5f, 1.5f);
				F32 g = 20 * oe::Random::get(0.5f, 1.0f);
				F32 b = 20 * oe::Random::get(0.5f, 1.0f);
				return oe::Color((U8)r, (U8)g, (U8)b);
			}));
			mParticles.emitParticles(100);
			setPositionZ(20);
			break;
		case Charge:
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 100.f, 200.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(2.0f, 2.0f), oe::Vector2(0.5f, 0.5f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.3f), oe::seconds(0.6f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distributions::colorGrade(oe::Color::Green, 0.6f, 1.f));
			mParticles.emitParticles(50);
			setPositionZ(-2);
			break;
		case Level:
			mParticles.setParticleVelocity(oe::Distributions::project(oe::Vector2(0.f, 1.f), 360.f, 100.f, 200.f));
			mParticles.setParticleScale(oe::Distributions::rect(oe::Vector2(2.0f, 2.0f), oe::Vector2(0.5f, 0.5f)));
			mParticles.setParticleLifetime(oe::Distributions::uniform(oe::seconds(0.3f), oe::seconds(0.6f)));
			mParticles.setParticleRotationSpeed(oe::Distributions::uniform(0.f, 180.f));
			mParticles.setParticleColor(oe::Distributions::colorGrade(oe::Color(30, 250, 220), 0.6f, 1.f));
			mParticles.emitParticles(50);
			setPositionZ(-2);
			break;
		default: break;
	}
}

void Fx::update(oe::Time dt)
{
	if (mParticles.getParticleCount() == 0)
	{
		kill();
	}
}
