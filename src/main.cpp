#include "sfml_window.hpp"

#include <exception>

int main()
{
	SFMLWindow sfmlWindow;

	try {
		sfmlWindow.Run();
	}
	catch (std::exception& e) {
		throw e;
	}

	return 0;
}