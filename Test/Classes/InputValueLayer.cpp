#include "InputValueLayer.h"

bool InputValue::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("inputScreen.png");
	sprite->setName("inputScreen");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite);

	label = LabelTTF::create("","Arial",24);
	label->setName("text");
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label);

	notice = LabelTTF::create("", "Arial", 24);
	notice->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	notice->setVisible(false);
	this->addChild(notice);

	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(InputValue::onKeyPress, this);
	listener->onKeyReleased = CC_CALLBACK_2(InputValue::onKeyRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	endVal = false;
	return true;
}

void InputValue::onKeyPress(EventKeyboard::KeyCode keyCode, Event *event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
		endVal = true;
		listener->setEnabled(false);
		break;
	default:
		if (keyCode >= EventKeyboard::KeyCode::KEY_0 && keyCode <= EventKeyboard::KeyCode::KEY_9)
		{
			if (notice->isVisible() == true)notice->setVisible(false);
			std::string str = label->getString();
			str.push_back(((int)keyCode-(int)EventKeyboard::KeyCode::KEY_0)+'0');
			if (str.length() > 3 || atoi(str.c_str())>255)
			{
				str.assign("");
				notice->setString("Error!");
				notice->setVisible(true);
			}
			label->setString(str);
		}
	}
}
void InputValue::onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event)
{

}
bool InputValue::isEnd()
{
	return endVal;
}