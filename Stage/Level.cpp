/******************************************
 * .tmx generated by Tiled Map Editor 0.12.3 (www.mapeditor.org)
 * .plist generated by Texture Packer 3.9.1 (CodeAndWeb GmbH)
 ******************************************/

#include "Level.h"
#include "LevelObject.h"
#include "Player.h"
#include "../Panel/GamePanel.h"

USING_NS_CC;

Level::Level(){
	this->schedule(schedule_selector(Level::update));
}

Scene* Level::createScene(){
	auto scene = Scene::createWithPhysics();
	auto layer = Level::create();
	layer->world = scene->getPhysicsWorld();
	layer->world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->addChild(layer);
	return scene;
}
Scene* Level::createSceneWithMap(std::string mapPath){
	auto scene = Scene::createWithPhysics();

	auto panel = GamePanel::createLayer();
	scene->addChild(panel, 1, panelTag);

	auto layer = Level::create();
	scene->addChild(layer, 0, levelTag);
	//PHYSICS WORLD SETUP
	layer->world = scene->getPhysicsWorld();
	layer->world->setGravity(Vec2(0.0f, -980.0f));
	layer->world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//TILED MAP SETUP
	layer->map = TMXTiledMap::create(mapPath);
	for (const auto& child : layer->map->getChildren()){
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}
	layer->addChild(layer->map);
	//TILED MAP PARSING
	layer->prepareLayers();
	layer->addObjects();

	return scene;
}

//PARSE ALL FIXTURES
void Level::prepareLayers(){
	for (auto& object : map->getChildren()){
		//TO TILE LAYER
		auto layer = dynamic_cast<TMXLayer*>(object);
		if (layer != nullptr)
			this->createFixtures(layer);
	}
}
void Level::createFixtures(TMXLayer* layer){
	auto layerSize = layer->getLayerSize();
	//FOR EACH TILE
	for (int y = 0; y < layerSize.height; y++){
		for (int x = 0; x < layerSize.width; x++){
			//GET SPRITE
			auto tileSprite = layer->getTileAt(Vec2(x, y)); //AUTO-addSprite
			if (tileSprite)
				this->createRectFixture(layer, tileSprite);
		}
	}
}
void Level::createRectFixture(TMXLayer* layer, Sprite* spr){
	//TILE SIZE CALCULATION
	auto tileSize = this->map->getTileSize();
	const float ppm = 32.0f; //pixel per meter

	//PHYSICS BODY
	auto body = PhysicsBody::createBox(Size(tileSize.width, tileSize.width));
	body->setDynamic(false);
	body->setMass(PHYSICS_INFINITY);
	body->setContactTestBitmask(0xFFFFFFFF);
	spr->setPhysicsBody(body);
}

//PARSE ALL OBJECTS
void Level::addObjects(){
	auto objGroups = map->getObjectGroups();
	for (auto& objGroup : objGroups){
		auto objs = objGroup->getObjects();
		for (auto& obj : objs){
			auto prop = obj.asValueMap();
			auto type = prop.at("type");
			if (!type.isNull()){
				//TO LEVEL OBJECT
				this->addObject(type.asString().c_str(), prop);
				this->objectCount++;
			}
		}
	}
}
void Level::addObject(std::string className, ValueMap& prop){
	LevelObject* obj = nullptr;
	if (className == "Player"){
		obj = new Player;
		setGamePanelOnPlayer((Player*)obj);
	}
	//else if (className == "Monster")
	//	obj = new Monster;

	if (obj != nullptr){
		obj->setProperties(prop);
		obj->addSpriteToLevel(this);
		obj->addBody();
	}
}
void Level::setGamePanelOnPlayer(Player* player){
	auto panel = (GamePanel*)(getScene()->getChildByTag(panelTag));
	panel->setPlayer(player);
}

void Level::update(float dt){
	//auto panel = (GamePanel*)(getScene()->getChildByTag(panelTag));
	//auto player = panel->getPlayer();
	//if (player){
	//	player->update();
	//}
}
