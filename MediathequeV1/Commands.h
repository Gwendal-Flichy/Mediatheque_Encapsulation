#pragma once


#include "Mediatheque.h"
using InstructionLine = std::string;
using InstructionLineList = std::vector<InstructionLine>;

class Commands
{
public:
	void process(const InstructionLine& instruction);
	void Input(const InstructionLine& instruction);

private:
	Mediatheque m_Mediatheque;
	std::vector<std::string> CommandHistory;

};