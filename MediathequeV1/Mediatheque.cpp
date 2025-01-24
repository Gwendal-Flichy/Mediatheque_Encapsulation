
#include "Mediatheque.h"

std::string MediaTypeToString(mediaType MediaType) {
    switch (MediaType) {
    case BOOK:
        return "BOOK";
    case MOVIE:
        return "MOVIE";
    case VIDEOGAME:
        return "VIDEOGAME";
    default:
        return "UNKNOWN";
    }
}

std::string MediaAvailableToString(bool available)
{
    if (available == false)
        return "unavailable";
    else
        return "available";

}

std::ostream& operator<<(std::ostream& s, const ClientFullName& fullName)
{
	s << fullName.LastName << " " << fullName.FirstName<<", ";
	return s;
}

bool operator==(const ClientFullName& fullName1, const ClientFullName& fullName2)
{
    return (fullName1.FirstName == fullName2.FirstName && fullName1.LastName == fullName2.LastName);
}


void Mediatheque::addClient(std::string lastName, std::string firstName, int age, std::string address, std::string phoneNumber, std::string mail)
{
    m_AllClients.push_back(new Client({ lastName ,firstName }, age, address, phoneNumber, mail));
}



void Mediatheque::listClient()
{

	for (auto it : m_AllClients)
	{
		std::cout << it->getClientFullName() << std::endl;
	}
}

void Mediatheque::removeClient(ClientFullName fullName) 
{
    bool clientFound = false;

    for (const auto& it : m_AllClients) {
        if (it->getClientFullName()==fullName) {
            clientFound = true;
            break;
        }
    }

    if (!clientFound) {
        std::cout << "Client : " << fullName << "not found" << std::endl;
        return;
    }

    m_AllClients.erase(
        std::remove_if(m_AllClients.begin(), m_AllClients.end(),
            [&fullName](Client* client) {
                return client->getClientFullName()==fullName;
            }),
        m_AllClients.end()
    );
}


void Mediatheque::removeClient(std::string mailOrPhoneNumber) 
{

    bool clientFound = false;

    for (const auto& it : m_AllClients) {
        if (it->getMail() == mailOrPhoneNumber || it->getPhoneNumber() == mailOrPhoneNumber) {
            clientFound = true;
            break;
        }
    }

    if (!clientFound) {
        std::cout << "Client mail or PhoneNumber : " << mailOrPhoneNumber << " not found" << std::endl;
        return;
    }

    m_AllClients.erase(
        std::remove_if(m_AllClients.begin(), m_AllClients.end(),
            [&mailOrPhoneNumber](Client* client) {

                return (client->getMail() == mailOrPhoneNumber ||
                    client->getPhoneNumber() == mailOrPhoneNumber);
            }),
        m_AllClients.end()
    );
}


void Mediatheque::addMedia(std::string Name, std::string ISBN)
{
    m_AllMedias.push_back(new Book(Name,ISBN));
}

void Mediatheque::addMedia(std::string Name, std::string Support, int AgeLimit)
{
    m_AllMedias.push_back(new Movie(Name, Support,AgeLimit));
}

void Mediatheque::addMedia(std::string Name, std::string Studio, int PEGI, std::string Type)
{
    m_AllMedias.push_back(new VideoGame(Name, Studio, PEGI, Type));
}



void Mediatheque::listMedia()
{
    for (auto it : m_AllMedias)
    {
        std::cout << it->getName() <<" : " << ::MediaTypeToString(it->getType()) <<std::endl;
    }


}


void Mediatheque::removeMedia(mediaType MediaType, std::string Name)
{
    bool MediaFound = false;

    for (const auto& it : m_AllMedias) {
        if (it->getType() == MediaType && it->getName() == Name) {
            MediaFound = true;
            break;
        }
    }

    if (!MediaFound) {
        std::cout << "Media : " << Name << " not found" << std::endl;
        return;
    }

    m_AllMedias.erase(
        std::remove_if(m_AllMedias.begin(), m_AllMedias.end(),
            [&MediaType, Name](IMedia* Media) {

                return (Media->getType() == MediaType &&
                    Media->getName() == Name);
            }),
        m_AllMedias.end()
    );
}



void Mediatheque::rent(ClientFullName fullName, mediaType MediaType, std::string MediaName)
{
    int Mediaidx=-1;
    for (auto i = 0; i < m_AllMedias.size()-1; ++i)
    {
        if (m_AllMedias[i]->getName() == MediaName && m_AllMedias[i]->getType() == MediaType)
        {
            Mediaidx = i;
            break;
        }
    }
    if (Mediaidx == -1)
    {
        std::cout << "Media" << MediaName << " not found" << std::endl;
        return;
    }
    if (m_AllMedias[Mediaidx]->available==false)
    {
        std::cout << "Media already rent" << std::endl;
        return;
    }

    for (auto it : m_AllClients)
    {
        if (it->getClientFullName() == fullName && it->ClientMedias.size() >= 5)
        {
            std::cout << "Client : "<< fullName << "already has 5 books or more" << std::endl;
            return;
        }

        if (it->getClientFullName() == fullName && it->ClientMedias.size()<5)
        {
            it->ClientMedias.push_back(m_AllMedias[Mediaidx]);
            m_AllMedias[Mediaidx]->available = false;
        }
    }

}


void Mediatheque::showMedia(ClientFullName fullName)
{
    for (auto it : m_AllClients)
    {
        if (it->getClientFullName() == fullName)
        {
            std::cout << fullName;
            for (auto clientM : it->ClientMedias)
            {
                
                std::cout<<clientM->getName() << " : " << ::MediaTypeToString(clientM->getType()) << "; ";
            }
        }
    }
    std::cout << std::endl;
}

void Mediatheque::showMedia(std::string mailOrPhoneNumber)
{
    for (auto it : m_AllClients)
    {
        if (it->getMail() == mailOrPhoneNumber || it->getPhoneNumber() == mailOrPhoneNumber)
        {
            std::cout << it->getClientFullName();
            for (auto clientM : it->ClientMedias)
            {
                
                std::cout << clientM->getName() << " : " << ::MediaTypeToString(clientM->getType()) << "; ";
            }
        }
    }
    std::cout << std::endl;
}




void Mediatheque::listMediaState()
{
    for (auto it : m_AllMedias)
    {
        std::cout << it->getName() << " : " << ::MediaTypeToString(it->getType()) << " | "<< MediaAvailableToString(it->available) << std::endl;
    }


}



void Mediatheque::who(mediaType MediaType, std::string MediaName)
{
    int Mediaidx = -1;
    for (auto i = 0; i < m_AllMedias.size() - 1; ++i)
    {
        if (m_AllMedias[i]->getName() == MediaName && m_AllMedias[i]->getType() == MediaType)
        {
            Mediaidx = i;
            break;
        }
    }
    if (Mediaidx == -1)
    {
        std::cout << "Media" << MediaName << " not found" << std::endl;
        return;
    }
    if (m_AllMedias[Mediaidx]->available == true)
    {
        std::cout << "Media is available" << std::endl;
        return;
    }

    for (auto it : m_AllClients)
    {
        for (auto clientM : it->ClientMedias)
        {
            if (clientM->getType() == MediaType && clientM->getName() == MediaName)
            {
                std::cout << it->getClientFullName();
            }
           
        }
    }

}


void Mediatheque::returnMedia(mediaType MediaType, std::string MediaName)
{
    int Mediaidx = -1;
    for (auto i = 0; i < m_AllMedias.size() - 1; ++i)
    {
        if (m_AllMedias[i]->getName() == MediaName && m_AllMedias[i]->getType() == MediaType)
        {
            Mediaidx = i;
            break;
        }
    }
    if (Mediaidx == -1)
    {
        std::cout << "Media" << MediaName << " not found" << std::endl;
        return;
    }
    if (m_AllMedias[Mediaidx]->available == true)
    {
        std::cout << "Media is available" << std::endl;
        return;
    }


    for (auto it : m_AllClients)
    {

        it->ClientMedias.erase(
            std::remove_if(it->ClientMedias.begin(), it->ClientMedias.end(),
                [&MediaType, MediaName](IMedia* Media) {

                    return (Media->getType() == MediaType &&
                        Media->getName() == MediaName);
                }),
            it->ClientMedias.end()

        );
    }

    m_AllMedias[Mediaidx]->available = true;
    


}