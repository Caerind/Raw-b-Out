#ifndef WRITINGTEXT_HPP
#define WRITINGTEXT_HPP

#include <SFML/Graphics/Text.hpp>

#include "../Engine/System/Time.hpp"

class WritingText : public sf::Text
{
	public:
		WritingText();

		void setString(const sf::String& string);

		sf::String getString() const;
		const sf::String& getCurrentString() const;

		void update(oe::Time dt);

		void setLettersPerSecond(F32 lettersPerSecond);
		F32 getLettersPerSecond() const;

		bool isWritten() const;

		oe::Time getRemainingTime() const;

	private:
		void passLetter();

	private:
		sf::String mString;
		oe::Time mElapsed;
		oe::Time mLimit;
		bool mWritten;
};

#endif // WRITINGTEXT_HPP
