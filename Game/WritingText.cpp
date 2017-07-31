#include "WritingText.hpp"

WritingText::WritingText()
{
	setLettersPerSecond(4.0f);
	mWritten = true;
}

void WritingText::setString(const sf::String& string)
{
	sf::Text::setString("");
	mString = string;
	mWritten = false;
	passLetter();
}

sf::String WritingText::getString() const
{
	return sf::Text::getString() + mString;
}

const sf::String& WritingText::getCurrentString() const
{
	return sf::Text::getString();
}

void WritingText::update(oe::Time dt)
{
	if (!mWritten)
	{
		mElapsed += dt;
		while (mElapsed > mLimit)
		{
			mElapsed -= mLimit;
			passLetter();
		}
	}
}

void WritingText::setLettersPerSecond(F32 lettersPerSecond)
{
	mLimit = oe::seconds(1.0f / lettersPerSecond);
}

F32 WritingText::getLettersPerSecond() const
{
	return 1.0f / mLimit.asSeconds();
}

bool WritingText::isWritten() const
{
	return mWritten;
}

oe::Time WritingText::getRemainingTime() const
{
	return mLimit * mString.getSize();
}

void WritingText::passLetter()
{
	if (mString.getSize() > 0)
	{
		sf::Text::setString(getCurrentString() + mString[0]);
		mString.erase(0, 1);
	}
	else
	{
		mWritten = true;
	}
}
