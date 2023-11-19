#pragma once

#include <SFML\Graphics.hpp>

class BaseGame
{
public:
	virtual void Update(float& dt) = 0;
	virtual void MouseEvent(sf::Event& event) = 0;
	virtual void KeyboardEvent(sf::Event& event) = 0;
	virtual void Draw() = 0;
	virtual ~BaseGame() = default;
};