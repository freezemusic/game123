#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class mainmenu : public Layer{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static Scene* createScene();

	// INIT
	void initGamePanel(int zvalue);
	void initStage(int zvalue);
	virtual bool init();

	// CALLBACK
	void menuCloseCallback(Ref* pSender);
	void menuLeftCallback(Ref* pSender);
	void menuRightCallback(Ref* pSender);
	void menuJumpCallback(Ref* pSender);
	
	CREATE_FUNC(mainmenu);
};

#endif // __HELLOWORLD_SCENE_H__