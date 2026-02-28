#include "Action.h"

std::string Action::name() const {
	return m_name;
}

std::string Action::type() const {
	return m_type;
}

Action::Action(std::string& name, std::string& type) {
	m_name = name;
	m_type = type;
}