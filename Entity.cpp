#include "Entity.h"

void Entity::destroy() {
	m_isActive = false;
}

std::string& Entity::getTag() {
	return m_tag;
}

int Entity::getID() {
	return m_id;
}