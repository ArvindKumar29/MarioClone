#include "Scene.h"

Scene::Scene(GameMode* gameMode) {

}


std::map<sf::Keyboard::Key, std::string>& Scene::getActionMap() {
	return m_actionMap;
}

void Scene::registerAction(sf::Keyboard::Key key, std::string actionName) {
	m_actionMap[key] = actionName;
}

void Scene::init() {

}