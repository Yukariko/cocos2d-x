#ifndef __PROBLEMLIST_H__
#define __PROBLEMLIST_H__

#include "Problem.h"
class Problem1 : public Problem
{
public:
	virtual void setSource();
	virtual void compile(cocos2d::Ref* pSender);
	CREATE_FUNC(Problem1);
};

#endif