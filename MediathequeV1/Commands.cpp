
#include "Commands.h"


using Token = std::string;
using TokenList = std::vector<Token>;

TokenList splitStringBySpace(const std::string& str)
{
    std::string workingStr = str;
    TokenList tokenList;

    while (true)
    {
        auto index = workingStr.find_first_of(' ');
        if (index == std::string::npos)
            break;

        std::string tmp(&workingStr[0], index);
        tokenList.push_back(tmp);
        workingStr = std::string(&workingStr[index + 1], workingStr.size() - (index + 1));
    }
    tokenList.push_back(workingStr);

    return tokenList;
}

TokenList removeEmptyTokens(const TokenList& tokens)
{
    TokenList result;
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] != "")
            result.push_back(tokens[i]);
    }
    return result;
}

TokenList splitIntoTokens(const std::string& str)
{
    return removeEmptyTokens(splitStringBySpace(str));
}

void Commands::process(const InstructionLine& instruction)
{
    std::vector<std::string> tokenList = splitIntoTokens(instruction);
    const std::string& instructionType = tokenList[0];

    if (instructionType == "addClient")
    {
        std::string address;
        std::string phoneNumber;

        for (auto i=4;i<tokenList.size() - 6;++i)
        {
			address = address + tokenList[i];
        }

        for (auto i = tokenList.size() - 6; i < tokenList.size() - 1; ++i)
        {
			phoneNumber = phoneNumber + tokenList[i];
        }

		m_Mediatheque.addClient(ClientFullName(tokenList[1], tokenList[2]), std::stoi(tokenList[3]), address, phoneNumber, tokenList[tokenList.size() - 1]);

    }


	else if (instructionType == "listClient")
    {
		if (tokenList.size() != 2)
		{
			std::cout << "Invalid number of arguments for listClient" << std::endl;
			return;
		}
		m_Mediatheque.listClient();
    }

	else if (instructionType == "removeClient")
    {
		if (tokenList.size() == 3)
            m_Mediatheque.removeClient(ClientFullName(tokenList[1], tokenList[2]));
		else if(tokenList.size() == 2)
            m_Mediatheque.removeClient(tokenList[1]);
		else
		{
			std::cout << "Invalid number of arguments for removeClient" << std::endl;
			return;
		}
    }
	else if (instructionType == "addMedia")
    {
        if(tokenList[1]=="BOOK")
		{
            if (tokenList.size() != 4)
            {
                std::cout << "Invalid number of arguments for addMedia BOOK" << std::endl;
                return;
            }
			if(tokenList[3].size()>13)
			{
				std::cout << "Invalid ISBN" << std::endl;
				return;
			}
			m_Mediatheque.addMedia(tokenList[2], tokenList[3]);
		}
        else if (tokenList[1] == "MOVIE")
        {
            if (tokenList.size() != 5)
			{
				std::cout << "Invalid number of arguments for addMedia MOVIE" << std::endl;
				return;
			}
			m_Mediatheque.addMedia(tokenList[2], tokenList[3], std::stoi(tokenList[4]));
		}
		else if (tokenList[1] == "VIDEOGAME")
		{
            if (tokenList.size() != 6)
            {
                std::cout << "Invalid number of arguments for addMedia VIDEOGAME" << std::endl;
                return;
            }
			m_Mediatheque.addMedia(tokenList[2], tokenList[3], std::stoi(tokenList[4]), tokenList[5]);
            
		}
		else
		{
			std::cout << "Invalid media type" << std::endl;
		}

    }
	else if (instructionType == "listMedia")
	{
		m_Mediatheque.listMedia();
	}
	else if (instructionType == "removeMedia")
	{
		if (tokenList.size() != 3)
		{
			std::cout << "Invalid number of arguments for removeMedia" << std::endl;
			return;
		}
		if (tokenList[1] == "BOOK")
		{
			m_Mediatheque.removeMedia(BOOK, tokenList[2]);
		}
		else if (tokenList[1] == "MOVIE")
		{
			m_Mediatheque.removeMedia(MOVIE, tokenList[2]);
		}
		else if (tokenList[1] == "VIDEOGAME")
		{
			m_Mediatheque.removeMedia(VIDEOGAME, tokenList[2]);
		}
		else
		{
			std::cout << "Invalid media type" << std::endl;
		}
	}
	else if (instructionType == "rent")
	{
		if (tokenList.size() != 5)
		{
			std::cout << "Invalid number of arguments for rent" << std::endl;
			return;
		}
		if (tokenList[3] == "BOOK")
		{
			m_Mediatheque.rent(ClientFullName(tokenList[1], tokenList[2]), BOOK, tokenList[4]);
		}
		else if (tokenList[3] == "MOVIE")
		{
			m_Mediatheque.rent(ClientFullName(tokenList[1], tokenList[2]), MOVIE, tokenList[4]);
		}
		else if (tokenList[3] == "VIDEOGAME")
		{
			m_Mediatheque.rent(ClientFullName(tokenList[1], tokenList[2]), VIDEOGAME, tokenList[4]);
		}
		else
		{
			std::cout << "Invalid media type" << std::endl;
		}
	}
	else if (instructionType == "showMedia")
	{
		if (tokenList.size() == 3)
		{
			m_Mediatheque.showMedia(ClientFullName(tokenList[1], tokenList[2]));
		}
		else if(tokenList.size() == 2)
		{
			m_Mediatheque.showMedia(tokenList[1]);
		}
		else
		{
			std::cout << "Invalid number of arguments for showMedia" << std::endl;
			return;
		}
	}
	else if (instructionType == "listMediaState")
	{
		if (tokenList.size() != 1)
		{
			std::cout << "Invalid number of arguments for listMediaState" << std::endl;
			return;
		}
		m_Mediatheque.listMediaState();
	}
	else if (instructionType == "who")
	{
		if (tokenList.size() != 3)
		{
			std::cout << "Invalid number of arguments for who" << std::endl;
			return;
		}
		if (tokenList[1] == "BOOK")
		{
			m_Mediatheque.who(BOOK, tokenList[2]);
		}
		else if (tokenList[1] == "MOVIE")
		{
			m_Mediatheque.who(MOVIE, tokenList[2]);
		}
		else if (tokenList[1] == "VIDEOGAME")
		{
			m_Mediatheque.who(VIDEOGAME, tokenList[2]);
		}
		else
		{
			std::cout << "Invalid media type" << std::endl;
		}
	}
	else if (instructionType == "returnMedia")
	{
		if (tokenList.size() != 3)
		{
			std::cout << "Invalid number of arguments for returnMedia" << std::endl;
			return;
		}
		if (tokenList[1] == "BOOK")
		{
			m_Mediatheque.returnMedia(BOOK, tokenList[2]);
		}
		else if (tokenList[1] == "MOVIE")
		{
			m_Mediatheque.returnMedia(MOVIE, tokenList[2]);
		}
		else if (tokenList[1] == "VIDEOGAME")
		{
			m_Mediatheque.returnMedia(VIDEOGAME, tokenList[2]);
		}
		else
		{
			std::cout << "Invalid media type" << std::endl;
		}
	}
	else if (instructionType == "exit")
	{
		exit(0);
	}
	else if (instructionType == "help")
	{
		std::cout << "Available instructions:" << std::endl;
		std::cout << "addClient [lastName] [firstName] [age] [address] [phoneNumber] [mail]" << std::endl;
		std::cout << "listClient" << std::endl;
		std::cout << "removeClient [lastName] [firstName] or [mail] or [phoneNumber]" << std::endl;
		std::cout << "addMedia BOOK [Name] [ISBN]" << std::endl;
		std::cout << "addMedia MOVIE [Name] [Support] [AgeLimit]" << std::endl;
		std::cout << "addMedia VIDEOGAME [Name] [Studio] [PEGI] [Type]" << std::endl;
		std::cout << "listMedia" << std::endl;
		std::cout << "removeMedia [MediaType] [Name]" << std::endl;
		std::cout << "rent [lastName] [firstName] [MediaType] [MediaName]" << std::endl;
		std::cout << "showMedia [lastName] [firstName] or [mail] or [phoneNumber]" << std::endl;
		std::cout << "listMediaState" << std::endl;
		std::cout << "who [MediaType] [MediaName]" << std::endl;
		std::cout << "returnMedia [MediaType] [MediaName]" << std::endl;
		std::cout << "exit" << std::endl;

	}
	else
	{
		std::cout << "Invalid instruction" << std::endl;
	}


}




