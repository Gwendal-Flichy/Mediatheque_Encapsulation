#pragma once


#include <string>

enum mediaType
{
	BOOK
   ,MOVIE
   ,VIDEOGAME

};

class IMedia
{
public:
	friend class Mediatheque;

	IMedia(std::string name)
		:m_name(name)
		,available(true)
	{}

	virtual ~IMedia() = default;

	std::string getName()
	{
		return m_name;
	}

	virtual int getAgeLimit() = 0;

	virtual mediaType getType() = 0;

protected:
	bool available;

private:

	std::string m_name;

};

