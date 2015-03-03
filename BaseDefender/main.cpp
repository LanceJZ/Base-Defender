#include "Game.h"

#include <stdexcept>
#include <iostream>

int main()
{
	try
	{
		Game game;
		game.Initialize();
		game.Run();
	}

	catch (std::exception& Except)
	{
		std::cout << "\nEXCEPTION: " << Except.what() << std::endl << std::endl;
		std::cout << "Hit Enter key." << std::endl;
		std::getchar();
	}
}