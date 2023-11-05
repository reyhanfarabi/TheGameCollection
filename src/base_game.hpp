#pragma once

#include <SFML\Graphics.hpp>

class BaseGame
{
public:
	virtual void Update(sf::Event& event) = 0;
	virtual void Draw() = 0;
	virtual ~BaseGame() = default;
};