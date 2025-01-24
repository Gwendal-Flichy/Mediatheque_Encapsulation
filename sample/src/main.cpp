#include <iostream>

#include "Commands.h"
int main()
{


	Commands commands;

	std::cout << "Bienvenue dans la Mediatheque. Tapez 'help' pour voir les commandes disponibles." << std::endl;

	while (true) {
		commands.Input();
	}


	return 0;
}