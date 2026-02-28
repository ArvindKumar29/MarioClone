#pragma once
#include "Entity.h"


class EntityManager
{
	std::vector<Entity*> m_entities;
	std::map<std::string, std::vector<Entity*>> m_entityMap;
	std::vector<Entity*> m_toAdd;
	int m_totalEntities;
	void init();

public:
	void update();
	Entity* addEntity(std::string tag);
	std::vector<Entity*> getEntities(std::string tag);
	std::vector<Entity*> getEntities();
};

