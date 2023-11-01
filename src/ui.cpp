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
		const sf::Color& textColor,
		const sf::Color& hoverTextColor,
		const sf::Color& bgColor,
		const sf::Color& hoverBgColor,
		const int& outlineThickness,
		const sf::Color& outlineColor,
		const sf::Color& hoverOutlineColor,
		const sf::Vector2f& position,
		sf::RenderWindow& window)
		:
		textColor(textColor),
		hoverTextColor(hoverTextColor),
		bgColor(bgColor),
		hoverBgColor(hoverBgColor),
		outlineColor(outlineColor),
		hoverOutlineColor(hoverOutlineColor),
		window(window),
		text(str, characterSize, textColor, position, window)
	{

		shape.setSize(sf::Vector2f(text.GetSize().x, text.GetSize().y * 2));
		shape.setFillColor(bgColor);
		shape.setOutlineThickness(outlineThickness);
		shape.setOutlineColor(outlineColor);
		SetPosition(position);
	}

	void Button::SetPosition(const sf::Vector2f& position)
	{
		// position will be set base on text center point instead of default 
		// top left corner
		shape.setPosition({
			// x-axis need to add 2 to make it center in the x-axis
			position.x - shape.getSize().x / 2 + X_CENTER_OFFSET,
			// y-axis need to add 8 to make it center in the y-axis
			position.y - shape.getSize().y / 2 + Y_CENTER_OFFSET
		});
	}

	void Button::Draw()
	{
		HoverButton();
		window.draw(shape);
		text.Draw();
	}

	void Button::HoverButton()
	{
		if (IsInsideButton())
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

	void Button::TriggerEvent(void(&f)())
	{
		// for now only intended for mouse
		// will add keyboard and controller support in the future.
		// event will also trigger when mouse is inside button bounds
		if (IsInsideButton())
		{
			f();
		}
	}

	bool Button::IsInsideButton()
	{
		return 
			sf::Mouse::getPosition(window).x >= shape.getPosition().x &&
			sf::Mouse::getPosition(window).x <= shape.getPosition().x + shape.getSize().x &&
			sf::Mouse::getPosition(window).y >= shape.getPosition().y &&
			sf::Mouse::getPosition(window).y <= shape.getPosition().y + shape.getSize().y;
	}
}
