#include "LevelObject.h"
USING_NS_CC;

void LevelObject::setProperties(ValueMap& prop){
	this->setPosition(Vec2(
		prop["x"].asFloat(),
		prop["y"].asFloat()
	));
	this->setFlippedX(false);
	this->setFlippedY(false);
}
