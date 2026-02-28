#include "SceneMenu.h"
#include <iostream>
#include "ScenePlay.h"

SceneMenu::SceneMenu(GameMode* gameMode) : Scene(game){
	game = gameMode;
	init();
	std::cout << "Last Scene Was: " << game->m_currentScene << "\n";

}

void SceneMenu::init() {
	menuStrings.push_back("SYSTEM PHAAD DENGE");
	menuStrings.push_back("Level 1");
	menuStrings.push_back("Level 2");
	menuStrings.push_back("Level 3");
	menuStrings.push_back("Quit");
	menuText.setFont(game->getAssets().getFont("UIFont"));
	menuIndex = 1;
	registerAction(sf::Keyboard::Up, "UP");
	registerAction(sf::Keyboard::Down, "DOWN");
	registerAction(sf::Keyboard::Enter, "ENTER");
	
}

void SceneMenu::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "DOWN" && menuIndex < menuStrings.size() - 1) {
			menuIndex += 1;
		}
		else if (action.name() == "UP" && menuIndex > 1) {
			menuIndex -= 1;
		}
		else if (action.name() == "ENTER" && menuIndex == 4) {
			game->window().close();
		}
		else if (action.name() == "ENTER") {
			ScenePlay* scene = new ScenePlay(game, menuStrings[menuIndex]);
			game->changeScene(menuStrings[menuIndex], scene);
		}
	}
}

void SceneMenu::sRender() {
	game->window().clear(sf::Color(100, 250, 255));
	menuText.setString(menuStrings[0]);
	menuText.setPosition(0.0f , game->window().getSize().y / 2.0f - 200.0f);
	menuText.setFillColor(sf::Color::Red);
	menuText.setCharacterSize(100);
	game->window().draw(menuText);
	for (int i = 1; i < menuStrings.size(); i++) {
		menuText.setString(menuStrings[i]);
		menuText.setPosition(0.0f, game->window().getSize().y / 2.0f  - 100.0f + 50.0f * i);
		menuText.setCharacterSize(50);
		if (i == menuIndex) {
			menuText.setFillColor(sf::Color::White);
		}
		else {
			menuText.setFillColor(sf::Color::Black);
		}
		game->window().draw(menuText);
	}
	game->window().display();
}

void SceneMenu::update() {
}