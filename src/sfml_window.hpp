#include "board.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\System\Clock.hpp>

#include <string>

class SFMLWindow
{
public:
	SFMLWindow();
	void Run();
	void Update();
	void Draw();

private:
	sf::RenderWindow window;
	sf::Clock clock;
	Board board;

	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;
	const std::string WINDOW_NAME = "SFML App";
	float dt = 0.0f;
};