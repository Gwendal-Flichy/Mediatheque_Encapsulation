#include <iostream>
#include "Mediatheque.h"

int main()
{
	Mediatheque test;

	test.addClient("JEAN", "Pierre", 20, "18 rue de mon cu", "0734242542", "oui1@ok.com");
	test.addClient("OUI", "paul", 20, "18 rue de mon cu", "0734242542", "oui@ok.com");
	test.addClient("OUI54", "paul", 20, "18 rue de mon cu", "0734242560", "oui5@ok.com");
	test.addClient("PAUL", "Pierre", 20, "18 rue de mon cu", "0734242542", "oui2@ok.com");

	test.listClient();

	std::cout << "\n";

	ClientFullName clientToRemove = { "OUI1", "paul" };
	test.removeClient(clientToRemove);

	test.listClient();

	std::cout << "\n";

	test.addMedia("OUIL", "1769405834756");
	test.addMedia("NONF", "DVD", 16);
	test.addMedia("LUc1", "Ubisoft", 10, "RPG");
	test.addMedia("LUc2", "Ubisoft", 10, "RPG");
	test.addMedia("LUc3", "Ubisoft", 10, "RPG");
	test.addMedia("LUc4", "Ubisoft", 10, "RPG");
	test.addMedia("LUc5", "Ubisoft", 10, "RPG");
	test.addMedia("LUc6", "Ubisoft", 10, "RPG");
	test.addMedia("NONFN", "DVD", 16);

	test.listMedia();

	std::cout << "\n";


	test.removeMedia(MOVIE, "NONF");

	std::cout << "\n";

	test.listMediaState();

	std::cout << "\n";



	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc1");
	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc2");
	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc3");
	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc4");
	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc5");
	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc6");

	std::cout << "\n";

	test.listMediaState();

	std::cout << "\n";

	ClientFullName clientMedias = { "OUI54", "paul" };
	test.showMedia(clientMedias);
	test.showMedia("0734242560");
	test.showMedia("oui5@ok.com");

	test.returnMedia(VIDEOGAME, "LUc3");
	test.returnMedia(VIDEOGAME, "LUc4");

	std::cout << "\n";

	test.listMediaState();

	std::cout << "\n";

	test.rent({ "OUI54","paul" }, VIDEOGAME, "LUc3");

	std::cout << "\n";

	test.listMediaState();

	std::cout << "\n";

	test.who(VIDEOGAME, "LUc3");

	return 0;
}