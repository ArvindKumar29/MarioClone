#pragma once
#include <string>

class Action
{
	std::string m_name ;
	std::string m_type;

public:
	Action(std::string& name, std::string& type);

	std::string name() const;
	std::string type() const;
};

