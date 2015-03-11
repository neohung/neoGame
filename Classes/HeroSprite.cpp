#include "HeroSprite.h"

HeroSprite::HeroSprite(std::string filename)
{
	if(initWithFile(filename.c_str()))
	{
		state = kStateIdle;
		speed = 2.0f;
	}
}

HeroSprite::~HeroSprite()
{

}

void HeroSprite::doMove(Vec2 velocity)
{
	
}