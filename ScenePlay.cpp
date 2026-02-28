#include "ScenePlay.h"
#include <iostream>
#include "Physics.h"
#include "SceneMenu.h"
#include <fstream>
#include "Vec2.h"

ScenePlay::ScenePlay(GameMode* gameMode, std::string levelName) : Scene(game){
	game = gameMode;
	//std::cout << "Last Scene Was: " << game->m_currentScene <<"\n";
	init(levelName);
}

void ScenePlay::init(std::string levelName){

	m_entityManager = new EntityManager();

	levelName = levelName + ".txt";

	std::fstream fin(levelName);
	if (!fin.is_open()) {
		std::cout << "Could not load level...";
		game->window().close();
	}
	std::string type, texName, animName;
	float gx, gy, v, hg;
	while (fin >> type) {
		
		if (type == "Window") {
			fin >> levelTotalWidth >> levelTotalHeight;
			levelTotalWidth *= 64;
			levelTotalHeight *= 64;
		}
		else if (type == "Tile") {
			fin >> texName >> gx >> gy;
			auto tile = m_entityManager->addEntity("Tile");
			tile->addComponent<cSprite>().image.setTexture(game->getAssets().getTexture(texName));
			tile->getComponent<cSprite>().image.setOrigin(tile->getComponent<cSprite>().image.getLocalBounds().width / 2, tile->getComponent<cSprite>().image.getLocalBounds().height / 2);
			tile->addComponent<cTransform>(gridToPixel(gx, gy, tile), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), 0.0f);
			tile->addComponent<cBoundingBox>(tile->getComponent<cSprite>().image.getGlobalBounds().width, tile->getComponent<cSprite>().image.getGlobalBounds().height);
		}
		else if (type == "Dec") {
			fin >> texName >> gx >> gy;
			auto dec = m_entityManager->addEntity("Dec");
			dec->addComponent<cSprite>().image.setTexture(game->getAssets().getTexture(texName));
			dec->addComponent<cTransform>(gridToPixel(gx, gy, dec), Vec2(0.0f, 0.0f), Vec2(1.0f, 1.0f), 0.0f);
		}
		else if (type == "Player") {
			fin >> texName >> gx >> gy;
			sSpawnPlayer(texName, gx, gy);
		}
		else if (type == "Enemy") {
			fin >> texName >> gx >> gy >> v >> animName >> hg;
			auto enemy = m_entityManager->addEntity("Enemy");
			enemy->addComponent<cSprite>().image.setTexture(game->getAssets().getTexture(texName));
			enemy->addComponent<cTransform>(gridToPixel(gx, gy, enemy), Vec2(v, 0.0f), Vec2(1.0f, 1.0f), 0.0f);
			enemy->addComponent<cBoundingBox>(enemy->getComponent<cSprite>().image.getGlobalBounds().width, enemy->getComponent<cSprite>().image.getGlobalBounds().height);
			enemy->getComponent<cSprite>().image.setOrigin(enemy->getComponent<cSprite>().image.getLocalBounds().width / 2, enemy->getComponent<cSprite>().image.getLocalBounds().height / 2);
			if (hg) enemy->addComponent<cGravity>();
			enemy->addComponent<cAnimation>(animName);
			//std::cout << "Enemy Spawned at: " << enemy->getComponent<cTransform>().pos.x << ", " << enemy->getComponent<cTransform>().pos.y << "\n";
			//game->window().draw(enemy->getComponent<cSprite>().image);
		}
	}
	
	//std::cout << "New Level loaded Successfully...";
	registerAction(sf::Keyboard::Space, "JUMP");
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");
	registerAction(sf::Keyboard::Escape, "PAUSE");
	registerAction(sf::Keyboard::G, "GRID");
	registerAction(sf::Keyboard::T, "TEXTURE");
	registerAction(sf::Keyboard::C, "COLLISSION");

	view.setSize(1920.0f, 1080.0f);
	//view.setCenter(std::min(m_player->getComponent<cTransform>().pos.x, 1920.0f / 2), std::min(m_player->getComponent<cTransform>().pos.y, 1080.0f / 2));
}

void ScenePlay::sDebug(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::G) {
		drawgrid = !drawgrid;
		std::vector<sf::Vertex> lines;
		if (drawgrid) {
			int i = 0;
			while (i < 30) {
				lines.push_back(sf::Vertex(sf::Vector2f(64 * i, 0.0f), sf::Color::White));
				lines.push_back(sf::Vertex(sf::Vector2f(64 * i, 1080.0f), sf::Color::White));
				lines.push_back(sf::Vertex(sf::Vector2f(0.0f, 64 * i), sf::Color::White));
				lines.push_back(sf::Vertex(sf::Vector2f(1920.0f, 64 * i), sf::Color::White));
				i++;
				//std::cout << 4 * i << " Points added!!!\n";
			}
			game->window().draw(lines.data(), lines.size(), sf::Lines);
		}
	}
	else if (key == sf::Keyboard::C) {
		if (drawbbox) {
			for (auto e : m_entityManager->getEntities()) {
				if (e->hasComponent<cBoundingBox>() && e->hasComponent<cTransform>()) {
					auto box = e->getComponent<cBoundingBox>();
					auto pos = e->getComponent<cTransform>().pos;
					box.BBox.setPosition(pos.x, pos.y);
					box.BBox.setFillColor(sf::Color(0, 0, 0, 0));
					box.BBox.setOutlineColor(sf::Color::Red);
					box.BBox.setOutlineThickness(5);
					game->window().draw(box.BBox);
				}
			}
		}
	}
}

void ScenePlay::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "PAUSE") {
			auto menu = new SceneMenu(game);
			game->window().setView(game->window().getDefaultView());
			game->changeScene("Menu", menu);
		}
		else if (action.name() == "GRID") {
			sDebug(sf::Keyboard::G);
		}
		else if (action.name() == "RIGHT") {
			m_player->getComponent<cInput>().right = true;
			m_player->getComponent<cSprite>().image.setScale(1.0f, 1.0f);
		}
		else if (action.name() == "LEFT") {
			m_player->getComponent<cInput>().left = true;
			m_player->getComponent<cSprite>().image.setScale(-1.0f, 1.0f);
		}
		else if (action.name() == "JUMP") {
			m_player->getComponent<cInput>().jump = true;
		}
		else if(action.name() == "COLLISSION"){
			drawbbox = !drawbbox;
			sDebug(sf::Keyboard::C);
		}
	}
	else if (action.type() == "END") {
		if (action.name() == "RIGHT") {
			m_player->getComponent<cInput>().right = false;
		}
		else if (action.name() == "LEFT") {
			m_player->getComponent<cInput>().left = false;
		}
		else if (action.name() == "JUMP") {
			m_player->getComponent<cInput>().jump = false;
		}
	}
}

void ScenePlay::update() {
	if (m_player->getComponent<cTransform>().pos.y > levelTotalHeight + 200.0f) {
		m_player->destroy();
		game->window().setView(game->window().getDefaultView());
		auto menu = new SceneMenu(game);
		game->changeScene("Menu", menu);
	}
	m_entityManager->update();
	sMovement();
	sCollision();
	sAnimation();
}

void ScenePlay::sRender() {
	game->window().clear(sf::Color(100, 250, 255));

	auto camX = std::max(m_player->getComponent<cTransform>().pos.x, 1920.0f / 2);
	auto camY = std::max(m_player->getComponent<cTransform>().pos.y, 1080.0f / 2);
	camX = std::min(camX, levelTotalWidth - (1920 / 2));
	camY = std::min(camY, levelTotalHeight - (1080 / 2));
	view.setCenter(camX, camY);
	game->window().setView(view);

	//std::cout << "Rendering Entity outside. \n";
	for (auto& e : m_entityManager->getEntities()) {
		if (e->hasComponent<cTransform>() && e->hasComponent<cSprite>()) {
			auto& ePos = e->getComponent<cTransform>();
			auto& eSpr = e->getComponent<cSprite>();
			/*std::cout << "🔍 " << e->getTag() << " DEBUG DATA : \n";
			std::cout << "   - Position: " << ePos.pos.x << ", " << e->getComponent<cTransform>().pos.y << "\n";
			std::cout << "   - Scale:    " << ePos.scale.x << ", " << ePos.scale.y << "\n";
			std::cout << "   - Texture Rect Width: " << eSpr.image.getTextureRect().width << "\n";*/


			eSpr.image.setPosition(e->getComponent<cTransform>().pos.x, ePos.pos.y);
			eSpr.image.setRotation(ePos.angle);
			//eSpr.image.setScale(ePos.scale.x, ePos.scale.y);
			game->window().draw(eSpr.image);
		}
	}
	if (drawbbox) {
		for (auto e : m_entityManager->getEntities()) {
			if (e->hasComponent<cBoundingBox>() && e->hasComponent<cTransform>()) {
				auto box = e->getComponent<cBoundingBox>();
				auto pos = e->getComponent<cTransform>().pos;
				box.BBox.setPosition(pos.x, pos.y);
				box.BBox.setFillColor(sf::Color(0, 0, 0, 0));
				box.BBox.setOutlineColor(sf::Color::White);
				box.BBox.setOutlineThickness(2);
				game->window().draw(box.BBox);
			}
		}
	}

	// DRAWING GRID FOR DEBUGGING IF IT WAS ALREADY THERE FOR THE LAST FRAME...
	if (drawgrid) {
		std::vector<sf::Vertex> lines;
		int i = 0;
		while (i < levelTotalWidth) {
			lines.push_back(sf::Vertex(sf::Vector2f(64 * i, 0.0f), sf::Color::White));
			lines.push_back(sf::Vertex(sf::Vector2f(64 * i, levelTotalHeight), sf::Color::White));
			lines.push_back(sf::Vertex(sf::Vector2f(0.0f, 64 * i), sf::Color::White));
			lines.push_back(sf::Vertex(sf::Vector2f(levelTotalWidth, 64 * i), sf::Color::White));
			i++;
			//std::cout << 4 * i << " Points added!!!\n";
		}
		game->window().draw(lines.data(), lines.size(), sf::Lines);
	}
	game->window().display();
}

void ScenePlay::sMovement() {
	// Player setting
	m_player->getComponent<cTransform>().vel.x = 0;
	auto& pInput = m_player->getComponent<cInput>();
	if (player_status == "GROUNDED" && pInput.jump) {
		m_player->getComponent<cTransform>().vel.y = -17;
		player_status = "JUMPING";
	}
	if (pInput.right) {
		m_player->getComponent<cTransform>().vel.x = 5;
	}
	if (pInput.left) {
		m_player->getComponent<cTransform>().vel.x = -5;
	}
	std::string animState = "PlayerIdle";
	if (player_status == "JUMPING"){
		animState = "PlayerJump";
	}
	else if (m_player->getComponent<cTransform>().vel.x != 0) {
		animState = "PlayerRun";
	}
	if (animState != m_player->getComponent<cAnimation>().name) {
		m_player->getComponent<cAnimation>().currentFrame = 0;
	}
	m_player->getComponent<cAnimation>().name = animState;
	
	//m_player->getComponent<cTransform>().vel.y += m_player->getComponent<cGravity>().gravity;

	// Movement for other
	for (auto& e : m_entityManager->getEntities()) {
		if (e->hasComponent<cTransform>() && e->hasComponent<cSprite>()) {
			auto& pos = e->getComponent<cTransform>().pos;
			auto& vel = e->getComponent<cTransform>().vel;
			e->getComponent<cTransform>().prevPos = e->getComponent<cTransform>().pos;
			pos.x += vel.x;
			pos.y += vel.y;
			if (e->hasComponent<cGravity>()) {
				e->getComponent<cTransform>().vel.y += e->getComponent<cGravity>().gravity;
			}
		}
	}
}

void ScenePlay::sSpawnPlayer(std::string texName, int gx, int gy) {
	m_player = m_entityManager->addEntity("Player");
	m_player->addComponent<cSprite>();
	m_player->getComponent<cSprite>().image.setTexture(game->getAssets().getTexture(texName), true); 
	m_player->getComponent<cSprite>().image.setOrigin(m_player->getComponent<cSprite>().image.getLocalBounds().width / 2 + 5.0f, m_player->getComponent<cSprite>().image.getLocalBounds().height / 2 + 15.0f);
	m_player->addComponent<cTransform>(gridToPixel(gx, gy, m_player), Vec2(0.0f, 0.0f), Vec2(1, 1), 0.0f);
	m_player->addComponent<cBoundingBox>(m_player->getComponent<cSprite>().image.getGlobalBounds().width - 20.0f, m_player->getComponent<cSprite>().image.getGlobalBounds().height - 30.0f);
	m_player->getComponent<cBoundingBox>().BBox.setOrigin(m_player->getComponent<cBoundingBox>().w / 2 - 5.0f , m_player->getComponent<cBoundingBox>().h / 2);
	m_player->addComponent<cInput>();
	m_player->addComponent<cGravity>();
	m_player->addComponent<cAnimation>("PlayerJump");
}

void ScenePlay::sCollision() {

	// COLLISSION RESOLUTION OF PLAYER WITH SURROUNDING WORLD
	for (auto& e : m_entityManager->getEntities()) {
		std::string name = e->getTag();
		if (e->hasComponent<cBoundingBox>() && name != "Player") {
			Vec2 overlap = Physics::getOverlap(m_player, e);
			Vec2 prevoverlap = Physics::getPrevOverlap(m_player, e);

			// CHECKING COLLISSION...
			if (overlap.x > 0 && overlap.y > 0) {

				// 1. VERTICAL COLLISION: Agar pichle frame mein X mein pehle se overlap tha, toh takkar pakka upar/niche hui hai!
				if (prevoverlap.x > 0) {

					// Player Above Entity (Niche gir raha hai)
					if (m_player->getComponent<cTransform>().prevPos.y < e->getComponent<cTransform>().prevPos.y) {
						if (e->getTag() == "Enemy") {
							e->destroy();
						}
						else {
							m_player->getComponent<cTransform>().pos.y -= overlap.y; // Bahar nikalo
							m_player->getComponent<cTransform>().vel.y = 0;          // Gravity roko
							player_status = "GROUNDED";
						}
					}
					// Entity Above Player (Sar par block laga)
					else {
						if (e->getTag() == "Enemy") {
							m_player->destroy();
							game->window().setView(game->window().getDefaultView());
							auto menu = new SceneMenu(game);
							game->changeScene("Menu", menu);
						}
						else {
							m_player->getComponent<cTransform>().pos.y += overlap.y;
							m_player->getComponent<cTransform>().vel.y = 0;
						}
					}
				}

				// 2. HORIZONTAL COLLISION: Agar pichle frame mein Y mein pehle se overlap tha, toh takkar pakka side se hui hai!
				else if (prevoverlap.y > 0) {
					if (e->getTag() == "Enemy") {
						m_player->destroy();
						game->window().setView(game->window().getDefaultView());
						auto menu = new SceneMenu(game);
						game->changeScene("Menu", menu);
					}
					// Player is to the left
					if (m_player->getComponent<cTransform>().prevPos.x < e->getComponent<cTransform>().prevPos.x) {
						m_player->getComponent<cTransform>().pos.x -= overlap.x;
					}
					// Player is to the right
					else {
						m_player->getComponent<cTransform>().pos.x += overlap.x;
					}
				}
			}
		}
	}

	// COLLISSION RESOLUTION OF DIFFERENT ENTITIES IN SURROUNDING WORLD

	for (auto& e : m_entityManager->getEntities("Enemy")) {
		for (auto& other : m_entityManager->getEntities()) {
			if (other->getTag() == "Block" || other->getTag() == "Tile") {
				auto overlap = Physics::getOverlap(e, other);
				auto prevoverlap = Physics::getPrevOverlap(e, other);
				
				if (overlap.x > 0 && overlap.y > 0) {
					if (prevoverlap.x > 0) {
						// Player Above Entity (Niche gir raha hai)
						if (e->getComponent<cTransform>().prevPos.y < other->getComponent<cTransform>().prevPos.y) {
							e->getComponent<cTransform>().pos.y -= overlap.y; // Bahar nikalo
							e->getComponent<cTransform>().vel.y = 0;          // Gravity roko
						}
						else {
							e->getComponent<cTransform>().pos.y += overlap.y;
							e->getComponent<cTransform>().vel.y = 0;
						}
					}

					// 2. HORIZONTAL COLLISION: Agar pichle frame mein Y mein pehle se overlap tha, toh takkar pakka side se hui hai!
					else if (prevoverlap.y > 0) {
						// Player is to the left
						if (e->getComponent<cTransform>().prevPos.x < other->getComponent<cTransform>().prevPos.x) {
							e->getComponent<cTransform>().pos.x -= overlap.x;
							e->getComponent<cTransform>().vel.x *= -1;
							e->getComponent<cSprite>().image.setScale(-1.0f, 1.0f);
						}
						// Player is to the right
						else {
							e->getComponent<cTransform>().pos.x += overlap.x;
							e->getComponent<cTransform>().vel.x *= -1;
							e->getComponent<cSprite>().image.setScale(-1.0f, 1.0f);
						}
					}
				}
			}
		}
	}
}

Vec2 ScenePlay::gridToPixel(float gx, float gy, Entity* entity) {
	
	if(!entity->hasComponent<cSprite>()) return Vec2(0.0f, 0.0f);
	
	gy = 17 - gy;


	// CONSIDERING THE LOCATION GRID COORDINATE GIVEN IS BOTTOM LEFT....
	auto px = gx * 64 + entity->getComponent<cSprite>().image.getTexture()->getSize().x / 2;
	auto py = gy * 64 - entity->getComponent<cSprite>().image.getTexture()->getSize().y / 2;
	return Vec2(px, py);
}

void ScenePlay::sAnimation() {
	for (auto& e : m_entityManager->getEntities()) {
		if (e->hasComponent<cAnimation>() && e->hasComponent<cSprite>()) {

			auto& cAnim = e->getComponent<cAnimation>();
			Animation& anim = game->getAssets().getAnimation(cAnim.name);
			if (anim.getFrames().empty()) {
				continue;
			}
			auto frameCount = anim.update(cAnim.name, cAnim.currentFrame, e);
			cAnim.currentFrame = frameCount;
		}
	}
}