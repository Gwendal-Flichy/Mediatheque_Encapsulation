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



class Book : public IMedia
{
public:
	Book(std::string name, std::string ISBN) :IMedia(name), m_ISBN(ISBN){}

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


class VideoGame : public IMedia
{
public:
	VideoGame(std::string name, std::string studio, int PEGI, std::string type):IMedia(name),m_studio(studio),m_PEGI(PEGI),m_type(type){}

	mediaType getType() override
	{
		return VIDEOGAME;
	}
	int getAgeLimit() override
	{
		return m_PEGI;
	}
	std::string getstudio()
	{
		return m_studio;
	}

private:
	std::string m_studio;
	int m_PEGI;
	std::string m_type;

};

class Movie : public IMedia
{
public:
	Movie(std::string name, std::string support, int ageLimit):IMedia(name), m_support(support), m_ageLimit(ageLimit) {}

	mediaType getType() override
	{
		return MOVIE;
	}
	int getAgeLimit() override
	{
		return m_ageLimit;
	}
	std::string getSupport()
	{
		return m_support;
	}
private:
	std::string m_support;
	int m_ageLimit;

};