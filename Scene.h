#pragma once
#include "Action.h"
#include <string>
#include <map>
#include "EntityManager.h"

class GameMode;

class Scene
{
	int currentFrame;
	std::map<sf::Keyboard::Key, std::string> m_actionMap;
	bool paused;
	bool hasEnded;
	EntityManager entities;

protected:
	GameMode* game;

public:
	Scene(GameMode* gameMode);
	void init();
	std::map<sf::Keyboard::Key, std::string>& getActionMap();
	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;
	void simulate(int n);
	//void doAction(Action action);
	void registerAction(sf::Keyboard::Key key, std::string actionName);
};

