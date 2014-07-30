#ifndef __INPUTVALUELAYER_H__
#define __INPUTVALUELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class InputValue : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	void onKeyPress(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event);
	bool isEnd();

	LabelTTF *label;
	LabelTTF *notice;
	EventListenerKeyboard *listener;
	bool endVal;
	CREATE_FUNC(InputValue);
};


#endif