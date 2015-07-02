#include "mainmenu.h"

USING_NS_CC;

enum
{
	kTagTileMap,
	kTagNode
};
Scene* mainmenu::createScene(){
	auto scene = Scene::create(); //AUTORELEASE
	auto layer = mainmenu::create(); //AUTORELEASE
	scene->addChild(layer);
	return scene;
}

// LAYER INIT
void mainmenu::initGamePanel(int zvalue){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(mainmenu::menuCloseCallback, this));
	closeItem->setPosition(Vec2(
		origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto leftButton = MenuItemImage::create(
		"arrowSilver_left.png",
		"arrowBlue_left.png",
		CC_CALLBACK_1(mainmenu::menuLeftCallback, this));
	leftButton->setScale(5.0);
	leftButton->setOpacity(160);
	leftButton->setPosition(Vec2(
		origin.x + leftButton->getContentSize().width * 5 / 2,
		origin.y + leftButton->getContentSize().width * 5 / 2));


	auto rightButton = MenuItemImage::create(
		"arrowSilver_right.png",
		"arrowBlue_right.png",
		CC_CALLBACK_1(mainmenu::menuRightCallback, this));
	rightButton->setScale(5.0);
	rightButton->setOpacity(160);
	rightButton->setPosition(Vec2(
		origin.x + rightButton->getContentSize().width * 10,
		origin.y + rightButton->getContentSize().width * 5 / 2));

	auto jumpButton = MenuItemImage::create(
		"buttonRound_grey.png",
		"buttonRound_blue.png",
		CC_CALLBACK_1(mainmenu::menuJumpCallback, this));
	jumpButton->setScale(3.0);
	jumpButton->setOpacity(160);
	jumpButton->setPosition(Vec2(
		origin.x + visibleSize.width - jumpButton->getContentSize().width * 5,
		origin.y + jumpButton->getContentSize().width * 5 / 2));

	auto menu = Menu::create(closeItem, jumpButton, leftButton, rightButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, zvalue);
}
void mainmenu::initStage(int zvalue){
	//BG_LAYER01(sky)
	auto bg = ParallaxNode::create();
	auto sky = CCSprite::create("bg.png");
	sky->setScale(0.5);
	sky->setAnchorPoint(Vec2(0, 0));
	bg->addChild(sky, 0, Vec2(0.5, 0.5), Vec2::ZERO);
	this->addChild(bg, zvalue, kTagNode);

	//BG_LAYER02(ground)
	auto map = TMXTiledMap::create("map2.tmx");
	this->addChild(map, zvalue, kTagTileMap);
	//ANTI-ALIASED
	for (const auto& child : map->getChildren()){
		static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
	}
}
bool mainmenu::init(){
	if (!Layer::init()){ return false; }

	//GAMEPANEL
	initGamePanel(1);
	initStage(0);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//TITLE
	auto label = Label::createWithTTF("sLIME", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	
	return true;
}

void mainmenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->popScene();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void mainmenu::menuLeftCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void mainmenu::menuRightCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void mainmenu::menuJumpCallback(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}