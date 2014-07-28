#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
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
    
	// custom function
	void setSource();
	void setMemory();
	void moveSource(int px, int py); 
	void moveMemory(int px, int py);
	void onkey(EventKeyboard::KeyCode keyCode, Event *event);
	
	// custom value
	bool smSwitch;
	int sourceX, sourceY;
	int memX,memY;
	LabelTTF *sourceMap[5];
	LabelTTF *memMap[16][8];
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};


#endif // __HELLOWORLD_SCENE_H__
