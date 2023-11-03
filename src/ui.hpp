#include <SFML\Graphics.hpp>

namespace UI
{
	//
	// TEXT UI
	//
	class Text
	{
	public:
		Text(
			const std::string& str,
			const int& characterSize,
			const sf::Color& color,
			const sf::Vector2f& position,
			sf::RenderWindow& window
		);

		void SetString(const std::string& str);
		void SetFillColor(const sf::Color& color);
		void SetPosition(const sf::Vector2f& position);
		sf::Vector2f GetSize();
		void Draw();

	private:
		sf::RenderWindow& window;
		sf::Font font;
		sf::Text text;
	};

	//
	// BUTTON UI
	//
	class Button
	{
	public:
		Button(
			const std::string& str,
			const int& characterSize,
			const sf::Color& textColor,
			const sf::Color& hoverTextColor,
			const sf::Color& bgColor,
			const sf::Color& hoverBgColor,
			const int& outlineThickness,
			const sf::Color& outlineColor,
			const sf::Color& hoverOutlineColor,
			const sf::Vector2f& position,
			sf::RenderWindow& window
		);

		void SetPosition(const sf::Vector2f& position);
		void Draw();
		void HoverButton();
		bool IsMouseInsideButton();
		bool IsTriggerable();

	private:
		static constexpr int X_CENTER_OFFSET = 2;
		static constexpr int Y_CENTER_OFFSET = 8;

		const sf::Color textColor;
		const sf::Color hoverTextColor;
		const sf::Color bgColor;
		const sf::Color hoverBgColor;
		const sf::Color outlineColor;
		const sf::Color hoverOutlineColor;

		sf::RenderWindow& window;
		sf::RectangleShape shape;
		Text text;
	};
}