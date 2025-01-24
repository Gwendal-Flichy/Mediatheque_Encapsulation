#pragma once
#include "IMedia.h"

class VideoGame : public IMedia
{
public:
	VideoGame(std::string name, std::string studio, int PEGI, std::string type) :IMedia(name), m_studio(studio), m_PEGI(PEGI), m_type(type) {}

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