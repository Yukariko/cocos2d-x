#include "LabelMap.h"

LabelMap::LabelMap(const std::string &str, const std::string &font, float fontSize)
{
	this->setString(str);
	this->setFontName(font);
	this->setFontSize(fontSize);
	this->color = Color3B::WHITE;
	this->master = nullptr;
}
void LabelMap::setMaster(LabelMap *master)
{
	this->master = master;
}
LabelMap *LabelMap::getMaster()
{
	return this->master;
}