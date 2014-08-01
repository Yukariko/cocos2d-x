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

	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPress, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	probLabel[0] = LabelTTF::create("Prob 1", "Arial", 24);
	probLabel[1] = LabelTTF::create("Prob 2", "Arial", 24);
	probLabel[2] = LabelTTF::create("Prob 3", "Arial", 24);
	nProblem = 3;
	for (int i = 0; i < nProblem; i++)
	{
		probLabel[i]->setPosition(Vec2(visibleSize.width / 2 - origin.x - 300 + 100 * i, visibleSize.height / 2 + origin.y));
		this->addChild(probLabel[i]);
	}
	selectProblem = 0;
	pushProblem = false;
	probLabel[selectProblem]->setColor(Color3B::RED);
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

void HelloWorld::onKeyPress(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (pushProblem)
	{
		auto prob = this->getChildByName("end");
		if (prob)
		{
			pushProblem = false;
			this->removeChild(prob);
		}
		return;
	}
	int px = 0, py = 0;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		px = -1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		px = 1;
		break;
	case EventKeyboard::KeyCode::KEY_TAB:

		break;
	case EventKeyboard::KeyCode::KEY_SHIFT:

		break;
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
		loadProblem(selectProblem);
		break;
	}
	probLabel[selectProblem]->setColor(Color3B::WHITE);
	selectProblem += px;
	if (selectProblem < 0) selectProblem = 0;
	else if (selectProblem >= nProblem) selectProblem = nProblem - 1;
	probLabel[selectProblem]->setColor(Color3B::RED);

}
void HelloWorld::onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SHIFT:

		break;
	}
}

void HelloWorld::loadProblem(int sel)
{
	pushProblem = true;
	switch (sel)
	{
	case 0:
		this->addChild(Problem1::create(),2);
		break;
	case 1:
		this->addChild(Problem1::create(),2);
		break;
	case 2:
		this->addChild(Problem1::create(),2);
		break;
	default:
		pushProblem = false;
		break;
	}
}