#include "ProblemList.h"
void Problem1::setSource()
{
	sourceCount = 1;
	sourceMap[0] = new LabelMap("int a;", "Arial", 24);
}
void Problem1::compile(cocos2d::Ref* pSender)
{
	int count = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (memMap[i][j]->getMaster() == sourceMap[sourceY])
				count++;
			if (memMap[i][j]->getString().compare("."))
			{
				count = -1;
				break;
			}
		}
	}
	log("%d", count);
	if (count == 4)
	{
		this->setName("end");
		//this->removeAllChildrenWithCleanup(true);
		listener->autorelease();
	}
	
}