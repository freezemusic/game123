#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "LevelObject.h"
#include "Level.h"
USING_NS_CC;

enum{ playerBatchTag, playerSpriteTag };

class Player : public LevelObject{
private:
	typedef LevelObject super;
	typedef Player self;
	Action* normalAnimation;
	bool isGround = false;
public:

	//void setProperties(ValueMap& prop);
	SpriteBatchNode* createBatch();
	Sprite* createSprite();
	void addSpriteToLevel(Level* const& level);
	void addBody();

	void move(Vec2& vec);
	void readyToJump(Vec2& vec);
	void rest();
	void jumping();

	void update();

	bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
	void onContactSeperate(PhysicsContact& contact);

	CREATE_FUNC(Player);
};

#endif //__PLAYER_H__