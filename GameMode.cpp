#include "GameMode.h"
#include "Assets.h"
#include "ScenePlay.h"
#include "SceneMenu.h"

void GameMode::init() {
	m_window.create(sf::VideoMode(1920, 1080), "!!!Super Mario Clone!!!");
	m_window.setFramerateLimit(60);
	m_window.setKeyRepeatEnabled(false);
	assets = Assets("Assets.txt");
	m_currentScene = "Menu";
	m_sceneMap[m_currentScene] = new SceneMenu(this);
}

GameMode::GameMode() {
	init();
}

void GameMode::run() {
	while (m_window.isOpen()) {
		sUserInput();
		update();
		currentScene()->sRender();
	}
}

void GameMode::update(){
	currentScene()->update();
}

Scene* GameMode::currentScene() {
	return m_sceneMap[m_currentScene];
}


Assets& GameMode::getAssets() {
	return assets;
}

void GameMode::changeScene(std::string name, Scene* scene) {
	scene->init();
	m_currentScene = name;
	m_sceneMap[m_currentScene] = scene;
}

void GameMode::sUserInput() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_window.close();
		}
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) {
				continue;
			}
			
			std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
			std::string actionName = currentScene()->getActionMap()[event.key.code];

			Action action(actionName, actionType);
			currentScene()->sDoAction(action);
		}
	}
}

sf::RenderWindow& GameMode::window() {
	return m_window;
}
