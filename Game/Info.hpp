#ifndef INFO_HPP
#define INFO_HPP

#include "../Engine/System/Prerequisites.hpp"

#include "../Engine/Math/Vector2.hpp"

class Info
{
	public:
		Info();

		void setString(const std::string& str);
		const std::string& getString() const;

		void setPosition(const oe::Vector2& position);
		const oe::Vector2& getPosition() const;

		void setId(U32 id);
		U32 getId() const;

		bool isVisible() const;

		bool update();

	private:
		std::string mString;
		oe::Vector2 mPosition;
		U32 mId;
		bool mVisible;

};

#endif // INFO_HPP
