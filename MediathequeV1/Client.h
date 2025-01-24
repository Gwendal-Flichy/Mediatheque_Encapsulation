#pragma once

#include <string>
#include <vector>
#include "Mediatheque.h"
#include "IMedia.h"


struct ClientFullName
{
	std::string LastName;
	std::string FirstName;

	ClientFullName(std::string _LastName, std::string _FirstName)
		:LastName(_LastName)
		,FirstName(_FirstName)
	{}
};



class Client
{
	
public:
	friend class Mediatheque;

	Client(ClientFullName fullName,int age, std::string address, std::string phoneNumber, std::string mail)
		:m_FullName(fullName)
		,m_age(age)
		,m_address(address)
		,m_phoneNumber(phoneNumber)
		,m_mail(mail)
	
	{}
	ClientFullName getClientFullName()
	{
		return m_FullName;

	}

	std::string getClientLastName()
	{
		return m_FullName.LastName;

	}
	std::string getClientFirstName()
	{

		return m_FullName.FirstName;
	}
	int getAge()
	{
		return m_age;
	}
	std::string getAddress()
	{
		return m_address;
	}
	std::string getMail()
	{

		return m_mail;
	}
	std::string getPhoneNumber()
	{
		return m_phoneNumber;

	}
protected:

	std::vector<IMedia*> ClientMedias;

private:

	ClientFullName m_FullName;
	int m_age;
	std::string m_address;
	std::string m_phoneNumber;
	std::string m_mail;
	
};