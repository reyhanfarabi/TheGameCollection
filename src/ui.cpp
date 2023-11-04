#include "ui.hpp"

#include <iostream>

namespace UI
{
	//
	// TEXT UI
	//
	Text::Text(
		const std::string& str, 
		const int& characterSize, 
		const sf::Color& color, 
		const sf::Vector2f& position,
		sf::RenderWindow& window)
		:
		window(window)
	{
		if (!font.loadFromFile("assets/fonts/Roboto-Regular.ttf"))
		{
			std::cerr << ".Error while loading font" << std::endl;
		}
		else
		{
			text.setFont(font);
			text.setString(str);
			text.setCharacterSize(characterSize);
			text.setFillColor(color);
			SetPosition(position);
		}
	}

	void Text::SetString(const std::string& str)
	{
		text.setString(str);
	}

	void Text::SetFillColor(const sf::Color& color)
	{
		text.setFillColor(color);
	}

	void Text::SetPosition(const sf::Vector2f& position)
	{
		// position will be set base on text center point instead of default 
		// top left corner
		text.setPosition({
			position.x - text.getGlobalBounds().width / 2,
			position.y - text.getGlobalBounds().height / 2,
		});
	}

	sf::Vector2f Text::GetSize()
	{
		return sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
	}

	void Text::Draw()
	{
		window.draw(text);
	}

	//
	// BUTTON UI
	//
	Button::Button(
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
		sf::RenderWindow& window)
		:
		PADDING(padding),
		textColor(textColor),
		hoverTextColor(hoverTextColor),
		bgColor(bgColor),
		hoverBgColor(hoverBgColor),
		outlineColor(outlineColor),
		hoverOutlineColor(hoverOutlineColor),
		window(window),
		text(str, characterSize, textColor, position, window)
	{
		shape.setSize(sf::Vector2f(
			text.GetSize().x + padding.right + padding.left,
			text.GetSize().y + padding.top + padding.bottom
		));
		shape.setFillColor(bgColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(outlineColor);
		SetShapePosition(position);
		SetTextPosition();
	}

	Button::Button(
		const std::string& str,
		const int& characterSize,
		const sf::Vector2f& position,
		const sf::Vector2f& size,
		const UI::Padding& padding,
		const sf::Color& textColor,
		const sf::Color& hoverTextColor,
		const sf::Color& bgColor,
		const sf::Color& hoverBgColor,
		const int& outlineThickness,
		const sf::Color& outlineColor,
		const sf::Color& hoverOutlineColor,
		sf::RenderWindow& window)
		:
		PADDING(padding),
		textColor(textColor),
		hoverTextColor(hoverTextColor),
		bgColor(bgColor),
		hoverBgColor(hoverBgColor),
		outlineColor(outlineColor),
		hoverOutlineColor(hoverOutlineColor),
		window(window),
		text(str, characterSize, textColor, position, window)
	{
		shape.setSize(sf::Vector2f(
			size.x + padding.right + padding.left,
			size.y + padding.top + padding.bottom
		));
		shape.setFillColor(bgColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(outlineColor);
		SetShapePosition(position);
		SetTextPosition();
	}

	void Button::SetShapePosition(const sf::Vector2f& position)
	{
		// position will be set base center point instead of default top left corner
		shape.setPosition({
			position.x - shape.getSize().x / 2,
			position.y - shape.getSize().y / 2
		});
	}

	void Button::SetTextPosition()
	{
		// position will be set automatically base center point of shape
		// instead of default top left corner.
		// no need for parameter.
		text.SetPosition(sf::Vector2f(
			shape.getPosition().x + shape.getSize().x / 2,
			shape.getPosition().y + shape.getSize().y / 2 -
			text.GetSize().y / 2 + text.GetSize().y / 5
		));
	}

	void Button::Draw()
	{
		HoverButton();
		window.draw(shape);
		text.Draw();
	}

	void Button::HoverButton()
	{
		if (IsMouseInsideButton())
		{
			text.SetFillColor(hoverTextColor);
			shape.setFillColor(hoverBgColor);
			shape.setOutlineColor(hoverOutlineColor);
		}
		else
		{
			text.SetFillColor(textColor);
			shape.setFillColor(bgColor);
			shape.setOutlineColor(outlineColor);
		}
	}

	void Button::SetButtonPosition(const sf::Vector2f& position)
	{
		SetShapePosition(position);
		SetTextPosition();
	}

	bool Button::IsMouseInsideButton()
	{
		return 
			sf::Mouse::getPosition(window).x >= shape.getPosition().x &&
			sf::Mouse::getPosition(window).x <= shape.getPosition().x + shape.getSize().x &&
			sf::Mouse::getPosition(window).y >= shape.getPosition().y &&
			sf::Mouse::getPosition(window).y <= shape.getPosition().y + shape.getSize().y;
	}

	bool Button::IsTriggerable()
	{
		return IsMouseInsideButton();
	}
}

