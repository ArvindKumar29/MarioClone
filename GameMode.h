#pragma once
#include "Scene.h"
#include "EntityManager.h"
#include "Assets.h"

class GameMode
{
	std::map<std::string, Scene*> m_sceneMap;
	sf::RenderWindow m_window;
	Assets assets;
	
	bool running;
	void init();
	Scene* currentScene();
	

public:
	std::string m_currentScene;
	GameMode();
	void run();
	void update();
	void quit();
	void changeScene(std::string name, Scene* scene);
	Assets& getAssets();
	void sUserInput();
	sf::RenderWindow& window();
};

