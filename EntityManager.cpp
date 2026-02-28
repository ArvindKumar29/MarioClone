#include "EntityManager.h"

void EntityManager::init() {}

// !!!UPDATING THE GAME!!!
void EntityManager::update() {
	
	// !!!REMOVING DEAD ENTITIES(!e->isActive)!!!
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [](auto e) {return !e->m_isActive; }), m_entities.end());

	// !!! ADDING NEW ENTITIES!!!
	for (auto e : m_toAdd) {
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}
	m_toAdd.clear();

}

// !!!ADDING AN ENTITY!!!
Entity* EntityManager::addEntity(std::string tag){
	Entity* e = new Entity(tag, m_totalEntities++);
	m_toAdd.push_back(e);
	return e;
}

// !!!GETTING ENTITIES OF A PARTICULAR TYPE!!!
std::vector<Entity*> EntityManager::getEntities(std::string tag){
	std::vector<Entity*> vec;
	for (auto e : m_entities) {
		if (e->m_tag == tag) {
			vec.push_back(e);
		}
	}
	return vec;
}

// !!!GETTING ALL ENTITEIES!!!
std::vector<Entity*> EntityManager::getEntities() {
	return m_entities;
}