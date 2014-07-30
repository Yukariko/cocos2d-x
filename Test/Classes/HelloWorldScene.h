#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "LabelMap.h"
#include "cocos2d.h"
#include "InputValueLayer.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuInputValue(cocos2d::Ref* pSender);

	// custom function
	void setInit();
	void initSource();
	void initMemory();
	void moveSource(int px, int py);
	void moveMemory(int px, int py);
	void setMemoryAllocate();
	void setMemoryClear();
	void setMemoryFree();
	void setMemoryBlue();
	void setMemoryShow();
	void setMemoryColorOrigin();

	void onKeyPress(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event);
	
	// custom value
	EventListenerKeyboard *listener;
	bool smSwitch,pushShift,pushEnter;
	int sourceCount, sourceY;
	int memX, memY;
	LabelMap *sourceMap[5];
	LabelMap *memMap[16][8];
	InputValue *myInput;
	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};


#endif // __HELLOWORLD_SCENE_H__