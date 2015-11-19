#include <iostream>
#include <cmath>
#include "sprite.h"
#include "gamedata.h"

Sprite::Sprite(const std::string& name, const Frame* const frame) :
	Drawable(name,
			Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
				Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
			Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
				Gamedata::getInstance().getXmlInt(name+"/speedY")) 
			),
	frame( frame ),
	frameWidth(frame->getWidth()),
	frameHeight(frame->getHeight()),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	accValue(Gamedata::getInstance().getXmlInt("physic/gravity"))
{ 
}

Sprite::Sprite(const Sprite& s) :
	Drawable(s),
	frame(s.frame),  // shallow copy; Manager may reuse it
	frameWidth(s.getFrame()->getWidth()),
	frameHeight(s.getFrame()->getHeight()),
	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
	worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
	accValue(Gamedata::getInstance().getXmlInt("physic/gravity"))
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
	Drawable::operator=(rhs);
	frame = rhs.frame;  // shallow copy; Manager may reuse it
	frameWidth = rhs.frameWidth;
	frameHeight = rhs.frameHeight;
	worldWidth = rhs.worldWidth;
	worldHeight = rhs.worldHeight;
	return *this;
}

void Sprite::draw() const { 
	Uint32 x = static_cast<Uint32>(X());
	Uint32 y = static_cast<Uint32>(Y());
	frame->draw(x, y); 
}

void Sprite::update(Uint32 ticks){
	posiUpdate(ticks);
}

void Sprite::posiUpdate(Uint32 ticks) { 
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);


}

void Sprite::shiftPosi(float x, float y)
{
	Vector2f incr = Vector2f(x, y);
	setPosition(getPosition()+incr);
}

void Sprite::speedUpdate(Uint32 ticks){
	fractionSpeedDown();
	gravity(ticks);
//	if ( Y() < 0) {
//		velocityY( abs( velocityY() )*0.9 );
//	}
//	if ( Y() > worldHeight-frameHeight) {
//		float i=1.0;
//		if(abs(velocityY())<0.2)
//			i  = 0.0;
//		velocityY( -abs( velocityY() )*0.9*i );
//	}

//	if ( X() < 0) {
//		velocityX( abs( velocityX() )*0.9 );
//	}
//	if ( X() > worldWidth-frameWidth) {
//		velocityX( -abs( velocityX() )*0.9 );
//	} 

}


void Sprite::randomSpeed(){
	int angle = rand()/360;
	int speed = velocityX()/100*(rand()%100);

	velocityX(speed*cos(angle/180*3.14));
	velocityY(speed*sin(angle/180*3.14));


}

void Sprite::fractionSpeedDown(){

	if(velocityX()>0)
		velocityX(velocityX()-velocityX()*velocityX()*0.00001);
	else 
		velocityX(velocityX()+velocityX()*velocityX()*0.00001);
	if(velocityY()>0)
		velocityY(velocityY()-velocityY()*velocityY()*0.00001);
	else
		velocityY(velocityY()+velocityY()*velocityY()*0.00001);
}


void Sprite::gravity(Uint32 ticks){
	float g=accValue;

	velocityY(velocityY()+g*ticks/1000);


}


void Sprite::gotoPosi(int x, int y){
	setPosition(	Vector2f(x,y));
}












