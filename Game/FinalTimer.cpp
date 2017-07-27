#include "FinalTimer.hpp"

FinalTimer::FinalTimer()
{
	mRunning = false;
	mExpired = false;
}

void FinalTimer::start(oe::Time duration)
{
	mRunning = true;
	mExpired = false;
	mDuration = duration;
	mStart = oe::Date();
	mEnd = mStart + duration;
}

void FinalTimer::update(oe::Time dt)
{
	if (mRunning)
	{
		mElapsed += dt;

		if (isExpired() && !isReallyExpired())
		{
			onExpire(mDuration);
			mExpired = true;
			mRunning = false;
		}
	}
}

void FinalTimer::cancel()
{
	mRunning = false;
	mExpired = true;
}

void FinalTimer::update()
{
	oe::Date now;
	if (now < mEnd)
	{
		mElapsed = mEnd - now;
	}
	else
	{
		mElapsed = mDuration;
	}
}

oe::Time FinalTimer::getDuration() const
{
	return mDuration;
}

oe::Time FinalTimer::getRemaingTime() const
{
	return mDuration - mElapsed;
}

bool FinalTimer::isExpired() const
{
	return mElapsed >= mDuration;
}

bool FinalTimer::isReallyExpired() const
{
	return mExpired;
}

bool FinalTimer::isRunning() const
{
	return mRunning;
}
