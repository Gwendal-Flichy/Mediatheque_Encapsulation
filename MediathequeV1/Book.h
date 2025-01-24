#pragma once
#include "IMedia.h"

class Book : public IMedia
{
public:
	Book(std::string name, std::string ISBN) :IMedia(name), m_ISBN(ISBN) {}

	mediaType getType() override
	{
		return BOOK;
	}
	int getAgeLimit() override
	{
		return 0;
	}
	std::string getISBN()
	{
		return m_ISBN;
	}
private:
	std::string m_ISBN;

};