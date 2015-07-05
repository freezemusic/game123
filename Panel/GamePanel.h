#ifndef __GAMEPANEL_H__
#define __GAMEPANEL_H__

#include "cocos2d.h"
class Player;
USING_NS_CC;

class GamePanel : public Layer{
private:
	typedef Layer super;
	typedef GamePanel self;
	Player* player;
	Label* debugLabel; //DEBUG
	DrawNode* pen;
	Point startLoc, endLoc;
public:
	static GamePanel* createLayer();

	bool isPlayerExist();
	void setPlayer(Player* player);
	Player* getPlayer();
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	CREATE_FUNC(GamePanel);
};

#endif // __GAMEPANEL_H__
