/*******************
 * Level is the main class create the Scene
 * and the Node Tree is as follow:
 * Scene{ 
 *    Level {Player, Monster, Fixtures, ...},
 *    GamePanel
 * }
 *******************/

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "cocos2d.h"
#include "../Panel/GamePanel.h"
class Player;
USING_NS_CC;

enum{ levelTag, panelTag };

class Level : public Layer{
private:
	PhysicsWorld* world;
	TMXTiledMap* map;
	int objectCount = 0;
public:
	Level();

	static Scene* createScene();
	static Scene* createSceneWithMap(std::string mapPath);

	//PARSE TMX TO OBJECTS
	void prepareLayers();
	void createFixtures(TMXLayer* layer);
	void createRectFixture(TMXLayer* layer, Sprite* spr);

	void addObjects();
	void addObject(std::string className, ValueMap& prop);
	void setGamePanelOnPlayer(Player* player);

	void update(float dt);

	CREATE_FUNC(Level);
};

#endif // __LEVEL_H__
