#ifndef __LEVEL_OBJECT_H__
#define __LEVEL_OBJECT_H__

#include "cocos2d.h"
class Level;
USING_NS_CC;

//VIRTUAL OBJECT
class LevelObject : public Sprite{
private:
	typedef Node super;
	typedef LevelObject self;
public:
	//LevelObject();
	//virtual ~LevelObject();

	void setProperties(ValueMap& prop);
	virtual SpriteBatchNode* createBatch() = 0;
	virtual Sprite* createSprite() = 0;
	virtual void addSpriteToLevel(Level* const& level) = 0;
	virtual void addBody() = 0;
	//virtual void addFixtures();

	//CREATE_FUNC(LevelObject);
};

#endif //__LEVEL_OBJECT_H__