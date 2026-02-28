#pragma once
#include "Scene.h"
#include "GameMode.h"

struct PlayerConfig{};

class ScenePlay :
    public Scene
{
    EntityManager* m_entityManager;
    std::string levelPath;
    Entity* m_player;
    std::string player_status;
    PlayerConfig playerConfig;
    bool drawgrid = false;
    bool drawbbox = false;
    void init(std::string levelName);
    sf::View view;
    float levelTotalWidth, levelTotalHeight;

public:
    
    void update();
    ScenePlay(GameMode* gameMode,std::string levelName);
    void sAnimation();
    Vec2 gridToPixel(float gx, float gy, Entity* entity);
    void sMovement();
    void sCollision();
    void sRender();
    void sDoAction(const Action& action) override;
    void sDebug(sf::Keyboard::Key key);
    void sSpawnPlayer(std::string texName, int gx, int gy);
};

