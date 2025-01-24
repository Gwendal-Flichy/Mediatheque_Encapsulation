#pragma once

#include<iostream>
#include <vector>
#include "Client.h"
#include "Media.h"



class Mediatheque
{
public:

	void addClient(std::string lastName, std::string firstName, int age, std::string address, std::string phoneNumber, std::string mail);

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

	std::vector<Client*> m_AllClients;
	std::vector<IMedia*> m_AllMedias;

};



