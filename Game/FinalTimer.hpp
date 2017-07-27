#ifndef FINALTIMER_HPP
#define FINALTIMER_HPP

#include "../Engine/System/Date.hpp"
#include "../Engine/System/Time.hpp"

#include "../Engine/Core/World.hpp"
#include "../Engine/Core/Systems/TimeSystem.hpp"

class FinalTimer
{
	public:
		FinalTimer();

		void start(oe::Time duration); // Start

		void update(oe::Time dt); // Update each frame

		void cancel(); // Cancel the timer

		void update(); // Update when returning back to the game

		OeSignal(onExpire, Time /*duration*/);

		oe::Time getDuration() const;
		oe::Time getRemaingTime() const;
		
		bool isExpired() const;
		bool isReallyExpired() const;
		bool isRunning() const;

	private:
		oe::Time mElapsed;
		oe::Time mDuration;
		oe::Date mStart;
		oe::Date mEnd;
		bool mExpired;
		bool mRunning;
};

#endif // FINALTIMER_HPP
