#pragma once
#include <vector>
#include <string>
#include <windows.h>

#include "Mediatheque.h"
using InstructionLine = std::string;
using InstructionLineList = std::vector<InstructionLine>;

class Commands
{
public:
	void process(const InstructionLine& instruction);
	void Input();

private:
	Mediatheque m_Mediatheque;
	std::vector<std::string> commandHistory;
	size_t historyIndex = 0;
};