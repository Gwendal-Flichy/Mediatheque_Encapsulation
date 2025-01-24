
#include "Mediatheque.h"
#include <algorithm>
#include <stdexcept>

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
    s << fullName.LastName << " " << fullName.FirstName << ", ";
    return s;
}

bool operator==(const ClientFullName& fullName1, const ClientFullName& fullName2)
{
    return (fullName1.FirstName == fullName2.FirstName && fullName1.LastName == fullName2.LastName);
}


bool operator<(const ClientFullName& fullName1, const ClientFullName& fullName2)
{
    if (fullName1.LastName != fullName2.LastName)
        return fullName1.LastName < fullName2.LastName;
    return fullName1.FirstName < fullName2.FirstName;
}

void Mediatheque::addClient(ClientFullName fullName, int age, std::string address, std::string phoneNumber, std::string mail)
{
    if (age < 0)
    {
        std::cout << "Client : " << fullName << " age cannot be negative" << std::endl;
        return;
    }

    if (m_AllClients.find(fullName) != m_AllClients.end()) {
        std::cout << "Client : "<< fullName << "already exists"<<std::endl;
        return;
    }

    m_AllClients[fullName] = new Client(fullName, age, address, phoneNumber, mail);
}

void Mediatheque::listClient()
{
    for (const auto& [fullName, client] : m_AllClients) {
        std::cout << fullName << std::endl;
    }
}

void Mediatheque::removeClient(ClientFullName fullName)
{
    auto it = m_AllClients.find(fullName);
    if (it == m_AllClients.end()) {
        std::cout << "Client : " << fullName << "not found" << std::endl;
        return;
    }
    if (!it->second->ClientMedias.empty())
    {
        std::cout << "Client : " << fullName << " has medias" << std::endl;
        return;
    }

    delete it->second;
    m_AllClients.erase(it);
}

void Mediatheque::removeClient(std::string mailOrPhoneNumber)
{
	
    auto it = std::find_if(m_AllClients.begin(), m_AllClients.end(),
        [&mailOrPhoneNumber](const auto& pair) {
            return pair.second->getMail() == mailOrPhoneNumber ||
                pair.second->getPhoneNumber() == mailOrPhoneNumber;
        });
    if (!it->second->ClientMedias.empty())
    {
        std::cout << "Client : " << it->second->getClientFullName() << " has medias" << std::endl;
        return;
    }
    if (it == m_AllClients.end()) {
        std::cout << "Client mail or PhoneNumber : " << mailOrPhoneNumber << " not found" << std::endl;
        return;
    }

    delete it->second;
    m_AllClients.erase(it);
}

void Mediatheque::addMedia(std::string Name, std::string ISBN)
{
    std::pair<mediaType, std::string> key = { BOOK, Name };
    if (m_AllMedias.find(key) != m_AllMedias.end()) {
        std::cout << "BOOK: " << Name << " already exists" << std::endl;
        return;
    }

    m_AllMedias[key] = new Book(Name, ISBN);
}

void Mediatheque::addMedia(std::string Name, std::string Support, int AgeLimit)
{
    if (AgeLimit < 0) {
        std::cout << "MOVIE: " << Name << " age limit cannot be negative" << std::endl;
        return;
    }

    std::pair<mediaType, std::string> key = { MOVIE, Name };
    if (m_AllMedias.find(key) != m_AllMedias.end()) {
        std::cout << "MOVIE: " << Name << " already exists" << std::endl;
        return;
    }

    m_AllMedias[key] = new Movie(Name, Support, AgeLimit);
}

void Mediatheque::addMedia(std::string Name, std::string Studio, int PEGI, std::string Type)
{
    if (PEGI < 0) {
        std::cout << "VIDEOGAME: " << Name << " PEGI cannot be negative" << std::endl;
        return;
    }

    std::pair<mediaType, std::string> key = { VIDEOGAME, Name };
    if (m_AllMedias.find(key) != m_AllMedias.end()) {
        std::cout << "VIDEOGAME: " << Name << " already exists" << std::endl;
        return;
    }

    m_AllMedias[key] = new VideoGame(Name, Studio, PEGI, Type);
}

void Mediatheque::listMedia()
{
    for (const auto& [key, media] : m_AllMedias) {
        std::cout << MediaTypeToString(key.first) << ": " << media->getName() << std::endl;
    }
}

void Mediatheque::removeMedia(mediaType MediaType, std::string Name)
{
    std::pair<mediaType, std::string> key = { MediaType, Name };
    auto it = m_AllMedias.find(key);
	if (it->second->available==false)
	{
		std::cout << MediaTypeToString(MediaType) << ": " << Name << " is rented" << std::endl;
		return;
	}

    if (it == m_AllMedias.end()) {
        std::cout << MediaTypeToString(MediaType) << ": " << Name << " not found" << std::endl;
        return;
    }

    delete it->second;
    m_AllMedias.erase(it);
}

void Mediatheque::rent(ClientFullName fullName, mediaType MediaType, std::string MediaName)
{
    std::pair<mediaType, std::string> key = { MediaType, MediaName };
    auto mediaIt = m_AllMedias.find(key);
    if (mediaIt == m_AllMedias.end()) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " not found" << std::endl;
        return;
    }

    if (mediaIt->second->available == false) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " is already rented" << std::endl;
        return;
    }

    auto clientIt = m_AllClients.find(fullName);
    if (clientIt == m_AllClients.end()) {
        std::cout << fullName << " not found" << std::endl;
        return;
    }

	if (clientIt->second->getAge() < mediaIt->second->getAgeLimit()) {
		std::cout << fullName << " is too young to rent " << MediaName << std::endl;
		return;
	}
        

    if (clientIt->second->ClientMedias.size() >= 5) {
        std::cout << fullName << " already has 5 medias or more" << std::endl;
        return;
    }

    clientIt->second->ClientMedias.push_back(mediaIt->second);
    mediaIt->second->available = false;
}

void Mediatheque::showMedia(ClientFullName fullName)
{
    for (const auto& [clientName, client] : m_AllClients) {
        if (clientName == fullName) {
            std::cout << fullName;
            for (auto clientM : client->ClientMedias) {
                std::cout << clientM->getName() << " : " << ::MediaTypeToString(clientM->getType()) << "; ";
            }
            std::cout << std::endl;
            return;
        }
    }
}

void Mediatheque::showMedia(std::string mailOrPhoneNumber)
{
    for (const auto& [clientName, client] : m_AllClients) {
        if (client->getMail() == mailOrPhoneNumber || client->getPhoneNumber() == mailOrPhoneNumber) {
            std::cout << client->getClientFullName();
            for (auto clientM : client->ClientMedias) {
                std::cout << clientM->getName() << " : " << ::MediaTypeToString(clientM->getType()) << "; ";
            }
            std::cout << std::endl;
            return;
        }
    }
}

void Mediatheque::listMediaState()
{
    for (const auto& [key, media] : m_AllMedias) {
        std::cout << MediaTypeToString(key.first) << ": " << media->getName()
            << " | " << MediaAvailableToString(media->available) << std::endl;
    }
}

void Mediatheque::who(mediaType MediaType, std::string MediaName)
{
    std::pair<mediaType, std::string> key = { MediaType, MediaName };
    auto mediaIt = m_AllMedias.find(key);
    if (mediaIt == m_AllMedias.end()) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " not found" << std::endl;
        return;
    }

    if (mediaIt->second->available == true) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " is available" << std::endl;
        return;
    }

    for (const auto& [clientName, client] : m_AllClients) {
        for (auto clientM : client->ClientMedias) {
            if (clientM->getName() == MediaName && clientM->getType() == MediaType) {
                std::cout << client->getClientFullName() << std::endl;
                return;
            }
        }
    }
}
void Mediatheque::returnMedia(mediaType MediaType, std::string MediaName)
{
    std::pair<mediaType, std::string> key = { MediaType, MediaName };
    auto mediaIt = m_AllMedias.find(key);
    if (mediaIt == m_AllMedias.end()) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " not found" << std::endl;
        return;
    }

    if (mediaIt->second->available == true) {
        std::cout << MediaTypeToString(MediaType) << ": " << MediaName << " is available" << std::endl;
        return;
    }

    for (auto& [clientName, client] : m_AllClients) {
        client->ClientMedias.erase(
            std::remove_if(client->ClientMedias.begin(), client->ClientMedias.end(),
                [&MediaName, MediaType](IMedia* Media) {
                    return Media->getName() == MediaName && Media->getType() == MediaType;
                }),
            client->ClientMedias.end()
        );
    }

    mediaIt->second->available = true;
}





