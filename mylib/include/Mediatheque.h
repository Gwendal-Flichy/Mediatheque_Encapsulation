#pragma once

#include <iostream>
#include <map>
#include <string>
#include "Client.h"
#include "IMedia.h"


class Mediatheque
{
public:

	void addClient(ClientFullName fullName, int age, std::string address, std::string phoneNumber, std::string mail);

	void listClient();

	void removeClient(ClientFullName fullName);

	void removeClient(std::string mailOrPhoneNumber);


	void addMedia(std::string Name, std::string ISBN);

	void addMedia(std::string Name, std::string Support, int AgeLimit);

	void addMedia(std::string Name, std::string Studio, int PEGI, std::string Type);

	void listMedia();

	void removeMedia(mediaType MediaType, std::string Name);
	
	void rent(ClientFullName fullName , mediaType MediaType, std::string MediaName);

	void showMedia(ClientFullName fullName);

	void showMedia(std::string mailOrPhoneNumber);

	void listMediaState();

	void who(mediaType MediaType, std::string MediaName);

	void returnMedia(mediaType MediaType, std::string MediaName);

private:

	std::map<ClientFullName, Client*> m_AllClients;
	std::map<std::pair<mediaType, std::string>, IMedia*> m_AllMedias;

};



