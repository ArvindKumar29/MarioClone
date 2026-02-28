#pragma once
#include "Scene.h"
#include "GameMode.h"

class SceneMenu :
    public Scene
{
    std::vector<std::string> menuStrings;
    sf::Text menuText;
    std::vector<std::string> levelPaths;
    int menuIndex;
    GameMode* game;
    void init();

public:
    SceneMenu(GameMode* gameMode);
    void update();
    void sRender();
    void sDoAction(const Action& action) override;
};

