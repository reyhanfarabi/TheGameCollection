#include <SFML\Graphics.hpp>

namespace UI
{
	//
	// PADDING STRUCT
	//
	struct Padding
	{
		float top;
		float right;
		float bottom;
		float left;

		Padding(float x, float y)
			:
			top(y),
			right(x),
			bottom(y),
			left(x)
		{}
		Padding(float top, float right, float bottom, float left)
			:
			top(top),
			right(right),
			bottom(bottom),
			left(left)
		{}
	};

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
			const sf::Vector2f& position,
			const UI::Padding& padding,
			const sf::Color& textColor,
			const sf::Color& hoverTextColor,
			const sf::Color& bgColor,
			const sf::Color& hoverBgColor,
			const int& outlineThickness,
			const sf::Color& outlineColor,
			const sf::Color& hoverOutlineColor,
			sf::RenderWindow& window
		);

		void Draw();
		void HoverButton();
		void SetButtonPosition(const sf::Vector2f& position);
		bool IsMouseInsideButton();
		bool IsTriggerable();

	private:
		void SetShapePosition(const sf::Vector2f& position);

	private:
		const UI::Padding PADDING;

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