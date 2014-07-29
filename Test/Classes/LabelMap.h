#ifndef __LABELMAP_H
#define __LABELMAP_H

#include "cocos2d.h"
USING_NS_CC;
class LabelMap : public cocos2d::LabelTTF
{
	
public:
	LabelMap(const std::string &str,const std::string &font,float fontSize);
	void setMaster(LabelMap *master);
	LabelMap *getMaster();

	Color3B color;
	LabelMap *master;
};
#endif