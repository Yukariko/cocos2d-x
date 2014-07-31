#include "HelloWorldScene.h"


Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	//auto layer2 = InputValue::create();
	// add layer as a child to scene
	scene->addChild(layer);
	//scene->addChild(layer2);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto inputValue = MenuItem::create(
		CC_CALLBACK_1(HelloWorld::menuInputValue, this));
	
	//
	inputValue->setPosition(Vec2(origin.x - visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,inputValue, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("screen.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setName("screen");
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	setInit();
	initSource();
	initMemory();
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPress, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuInputValue(Ref* pSender)
{
	log("ha");
}

void HelloWorld::setInit()
{
	sourceY = 0;
	memX = 0;
	memY = 0;
	smSwitch = false;
	pushShift = false;
	pushEnter = false;
	myInput = NULL;
}
void HelloWorld::initSource()
{
	sourceCount = 1;
	sourceMap[0] = new LabelMap("int a;", "Arial", 24);
	sourceMap[1] = new LabelMap("int a;", "Arial", 24);
	sourceMap[2] = new LabelMap("int b;", "Arial", 24);
	sourceMap[3] = new LabelMap("a=3;", "Arial", 24);
	sourceMap[4] = new LabelMap("}", "Arial", 24);
	float x = this->getChildByName("screen")->getPositionX() - 250;
	float y = this->getChildByName("screen")->getPositionY() + 200;
	for (int i = 0; i < sourceCount; i++)
	{
		sourceMap[i]->setPosition(Vec2(x, y));
		y -= 55;
		this->addChild(sourceMap[i], 2);
	}
}

void HelloWorld::initMemory()
{
	float x = this->getChildByName("screen")->getPositionX() + 50;
	float y = this->getChildByName("screen")->getPositionY() + 200;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			memMap[i][j] = new LabelMap(".","Arial",20);
			memMap[i][j]->setPosition(Vec2(x + j * 40, y - i * 20));
			this->addChild(memMap[i][j], 3);
		}
	}
}

void HelloWorld::onKeyPress(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (myInput)
	{
		if(!myInput->isEnd())return;
		else
		{
			if (!myInput->label->getString().empty())
			{
				memMap[memY][memX]->str.assign(myInput->label->getString());
				memMap[memY][memX]->setOwnString();
			}
			else
			{
				memMap[memY][memX]->str.assign(".");
				memMap[memY][memX]->setString(memMap[memY][memX]->str);
			}
			this->getScene()->removeChild(myInput);
			myInput = NULL;
			return;
		}
	}
	int px = 0, py = 0;
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
		smSwitch = !smSwitch;
		pushEnter = false;
		if (smSwitch == false)
		{
			sourceMap[sourceY]->setColor(Color3B::WHITE);
		}
		else
		{
			memMap[memY][memX]->setOwnString();
			memMap[memY][memX]->setOwnColor();
			setMemoryBlue();
		}
		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:
		if (smSwitch == false)
		{
			pushShift = true;
			setMemoryFree();
		}
		break;
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
		if (smSwitch == true)
		{
			sourceMap[sourceY]->setColor(Color3B::ORANGE);
			smSwitch = !smSwitch;
			pushEnter = true;
			setMemoryShow();
		}
		else
		{
			myInput = InputValue::create();
			myInput->setVisible(true);
			this->getScene()->addChild(myInput);
			log("hh");
		}
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
void HelloWorld::onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SHIFT:
		pushShift = false;
		if (pushEnter)
		{
			setMemoryAllocate();
		}
		else
		{
			setMemoryColorOriginAll();
		}
		memMap[memY][memX]->setColor(Color3B::RED);
		break;
	}
}
void HelloWorld::moveSource(int px, int py)
{
	sourceMap[sourceY]->setColor(Color3B::WHITE);
	sourceY += py;
	if (sourceY < 0) sourceY = 0;
	else if (sourceY > sourceCount-1) sourceY = sourceCount-1;
	sourceMap[sourceY]->setColor(Color3B::RED);
}
void HelloWorld::moveMemory(int px, int py)
{
	memMap[memY][memX]->setOwnString();
	if (pushShift == false) setMemoryColorOrigin();

	memX += px;
	memY += py;
	if (memX > 7){ memX = 0; memY += 1; }
	else if (memX < 0) { memX = 7; memY -= 1; }
	if (memY < 0) { memY = 0; memX = 0; }
	else if (memY > 15){ memY = 15; memX = 7; }
	memMap[memY][memX]->setString("|");
	memMap[memY][memX]->setColor(Color3B::RED);
}
void HelloWorld::setMemoryAllocate()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (memMap[i][j]->getColor() == Color3B::RED)
			{
				memMap[i][j]->setColor(Color3B::ORANGE);
				memMap[i][j]->color = Color3B::ORANGE;
				memMap[i][j]->setMaster(sourceMap[sourceY]);
			}
		}
	}
}
void HelloWorld::setMemoryClear()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (memMap[i][j]->getColor() == Color3B::RED)
			{
				memMap[i][j]->setColor(Color3B::WHITE);
			}
		}
	}
}
void HelloWorld::setMemoryFree()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pushEnter && memMap[i][j]->getMaster() == sourceMap[sourceY])
			{
				memMap[i][j]->setColor(Color3B::WHITE);
				memMap[i][j]->master = NULL;
				memMap[i][j]->color = Color3B::WHITE;
			}
		}
	}
}
void HelloWorld::setMemoryBlue()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (memMap[i][j]->getColor() == Color3B::ORANGE)
			{
				memMap[i][j]->setColor(Color3B::BLUE);
			}
		}
	}
}
void HelloWorld::setMemoryShow()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (memMap[i][j]->getMaster() == sourceMap[sourceY])
			{
				memMap[i][j]->setColor(Color3B::ORANGE);
			}
		}
	}
}
void HelloWorld::setMemoryColorOrigin()
{
	if (memMap[memY][memX]->color == Color3B::ORANGE)
	{
		if (pushEnter&&memMap[memY][memX]->getMaster() == sourceMap[sourceY])
		{
			memMap[memY][memX]->setColor(Color3B::ORANGE);
		}
		else
		{
			memMap[memY][memX]->setColor(Color3B::BLUE);
		}
	}
	else
	{
		memMap[memY][memX]->setColor(Color3B::WHITE);
	}
}
void HelloWorld::setMemoryColorOriginAll()
{
	for (int i = 0; i < 16; i++) for (int j = 0; j < 8; j++)
	{
		if (memMap[i][j]->color == Color3B::ORANGE)
		{
			if (pushEnter&&memMap[i][j]->getMaster() == sourceMap[sourceY])
			{
				memMap[i][j]->setColor(Color3B::ORANGE);
			}
			else
			{
				memMap[i][j]->setColor(Color3B::BLUE);
			}
		}
		else
		{
			memMap[i][j]->setColor(Color3B::WHITE);
		}
	}
}