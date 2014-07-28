#include "HelloWorldScene.h"



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("screen.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setName("screen");
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	setSource();
	setMemory();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onkey,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::setSource()
{
	sourceMap[0] = LabelTTF::create("int main() {","Arial",24);
	sourceMap[1] = LabelTTF::create("int a=5;", "Arial", 24);
	sourceMap[2] = LabelTTF::create("int b=3;", "Arial", 24);
	sourceMap[3] = LabelTTF::create("a=a*b;", "Arial", 24);
	sourceMap[4] = LabelTTF::create("}", "Arial", 24);
	float x = this->getChildByName("screen")->getPositionX() - 250;
	float y = this->getChildByName("screen")->getPositionY() + 200;
	for (int i = 0; i < 5; i++)
	{
		sourceMap[i]->setPosition(Vec2(x, y));
		y -= 55;
		this->addChild(sourceMap[i], 2);
	}
	sourceX = 0;
	sourceY = 0;
}

void HelloWorld::setMemory()
{
	float x = this->getChildByName("screen")->getPositionX() + 150;
	float y = this->getChildByName("screen")->getPositionY() + 200;
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			memMap[i][j] = LabelTTF::create(".","Arial",20);
			memMap[i][j]->setPosition(Vec2(x+j*20,y-i*20));
			this->addChild(memMap[i][j], 3);
		}
	}
	memX = 0;
	memY = 0;
	smSwitch = false;
}

void HelloWorld::onkey(EventKeyboard::KeyCode keyCode, Event *event)
{
	int px=0, py=0;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		py = -1;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		py = 1;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		px = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		px = 1;
		break;
	case EventKeyboard::KeyCode::KEY_TAB:
		if (smSwitch)
		{
			sourceMap[sourceY]->setColor(Color3B::WHITE);
		}
		else
		{
			memMap[memY][memX]->setString(".");
			memMap[memY][memX]->setColor(Color3B::WHITE);
		}
		smSwitch = !smSwitch;
		break;
	}
	if (smSwitch)
	{
		moveSource(px, py);
	}
	else
	{
		moveMemory(px, py);
	}
}
void HelloWorld::moveSource(int px, int py)
{
	sourceMap[sourceY]->setColor(Color3B::WHITE);
	sourceY += py;
	if (sourceY < 0) sourceY = 0;
	else if (sourceY > 4) sourceY = 4;
	sourceMap[sourceY]->setColor(Color3B::RED);
}
void HelloWorld::moveMemory(int px, int py)
{
	memMap[memY][memX]->setString(".");
	memMap[memY][memX]->setColor(Color3B::WHITE);
	memX += px;
	memY += py;
	if (memX > 7){ memX = 0; memY += 1; }
	else if (memX < 0) { memX = 7; memY -= 1; }
	if (memY < 0) { memY = 0; memX = 0; }
	else if (memY > 15){ memY = 15; memX = 7; }
	memMap[memY][memX]->setString("|");
	memMap[memY][memX]->setColor(Color3B::RED);
}