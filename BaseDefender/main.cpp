#include "Game.h"
#include <stdexcept>
#include <iostream>

std::unique_ptr<Game> pGame(new Game());

int main()
{
	try
	{
		pGame->Initialize();
		pGame->Run();
	}

	catch (std::exception& Except)
	{
		std::cout << "\nEXCEPTION: " << Except.what() << std::endl << std::endl;
		std::cout << "Hit Enter key." << std::endl;
		std::getchar();
	}
}