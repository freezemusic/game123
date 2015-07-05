#include "Player.h"
#include "Level.h"
USING_NS_CC;

SpriteBatchNode* Player::createBatch(){
	auto spriteBatch = SpriteBatchNode::create("slime_sprite.png");
	return spriteBatch;
}
Sprite* Player::createSprite(){
	auto sprCache = SpriteFrameCache::getInstance();
	sprCache->addSpriteFramesWithFile("slime_sprite.plist");
	this->setSpriteFrame("slime01.png");
	//NORMAL ANIMATION
	auto animation = Animation::create();
	char str[100] = { 0 };
	for (int i = 1; i <= 4; i++){
		sprintf(str, "slime0%d.png", i);
		animation->addSpriteFrame(sprCache->spriteFrameByName(str));
	}
	animation->setDelayPerUnit(0.2f);
	normalAnimation = RepeatForever::create(Animate::create(animation));
	normalAnimation->retain();
	this->runAction(normalAnimation);
	return(this);
}
void Player::addSpriteToLevel(Level* const& level){
	auto batch = createBatch();
	auto sprite = createSprite();
	sprite->setName("Player");
	batch->addChild(sprite, 0, playerSpriteTag);
	level->addChild(batch, 0, playerBatchTag);
}
void Player::addBody(){
	auto body = PhysicsBody::createCircle(this->getContentSize().height*0.6f / 2);
	body->setRotationEnable(false);
	body->setContactTestBitmask(0xFFFFFFFF);
	this->setPhysicsBody(body);
	//COLLISION CALLBACK
	setName("Player");
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactPreSolve = CC_CALLBACK_2(Player::onContactPreSolve, this);
	contactListener->onContactSeperate = CC_CALLBACK_1(Player::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Player::move(Vec2& vec){
	if (!isGround) return;
	this->setSpriteFrame("slime04.png");
	if (vec.length() > 300){
		vec.normalize();
		vec.scale(300);
	}
	vec.scale(200); //IMPULSE SCALE
	this->getPhysicsBody()->applyImpulse(vec);
	this->setFlippedX(vec.x < 0);
}
void Player::readyToJump(Vec2& vec){
	this->stopAllActions();
	if (vec.length() > 250){
		this->setSpriteFrame("slime02.png");
	}
	else if (vec.length() > 30){
		this->setSpriteFrame("slime01.png");
	}
	else{
		this->setSpriteFrame("slime04.png");
	}
	this->setFlippedX(vec.x < 0);
}
void Player::rest(){
	if (!(bool)getNumberOfRunningActions())
		runAction(normalAnimation);
}
void Player::jumping(){
	stopAllActions();
	setSpriteFrame("slime04.png");
}

void Player::update(){
}

bool Player::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve){
	if (isGround) return true;
	auto nodeA = (Sprite*)(contact.getShapeA()->getBody()->getNode());
	auto nodeB = (Sprite*)(contact.getShapeB()->getBody()->getNode());
	if (nodeA && nodeB){
		auto player = (Player*)((nodeA->getName() == "Player") ? nodeA : (nodeB->getName() == "Player") ? nodeB : nullptr);
		if (!player) return true;
		player->isGround = true;
		player->rest();
	}
	return true;
}
void Player::onContactSeperate(PhysicsContact& contact){
	if (!isGround) return;
	auto nodeA = (Sprite*)(contact.getShapeA()->getBody()->getNode());
	auto nodeB = (Sprite*)(contact.getShapeB()->getBody()->getNode());
	if (nodeA && nodeB){
		auto player = (Player*)((nodeA->getName() == "Player") ? nodeA : (nodeB->getName() == "Player") ? nodeB : nullptr);
		if (!player) return;
		player->isGround = false;
		player->jumping();
	}
}