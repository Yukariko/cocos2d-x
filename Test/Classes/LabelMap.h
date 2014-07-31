#ifndef __LABELMAP_H
#define __LABELMAP_H

#include "cocos2d.h"
USING_NS_CC;
class LabelMap : public cocos2d::LabelTTF
{
	
public:
	LabelMap(const std::string &str,const std::string &font,float fontSize);
	void setMaster(LabelMap *master);
	void setOwnString();
	void setOwnColor();

	LabelMap *getMaster();

	Color3B color;
	std::string str;
	LabelMap *master;
};
#endif