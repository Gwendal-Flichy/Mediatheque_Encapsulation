#pragma once
#include "IMedia.h"

class Movie : public IMedia
{
public:
	Movie(std::string name, std::string support, int ageLimit) :IMedia(name), m_support(support), m_ageLimit(ageLimit) {}

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