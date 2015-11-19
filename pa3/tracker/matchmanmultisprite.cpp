#include"matchmanmultisprite.h"
#include"gamedata.h"
MatchmanMultiSprite::MatchmanMultiSprite(const std::string& name):
	MultiSprite(name),
	status(0),
	frameOffset(0),
	lastXPos(X()),
	paceLength(Gamedata::getInstance().getXmlInt(name+"/paceratio"))
	{
}


void MatchmanMultiSprite::update(Uint32 ticks) { 

	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	if ( Y() < 0) {
		velocityY( abs( velocityY() ) );
	}
	if ( Y() > worldHeight-frameHeight) {
		velocityY( -abs( velocityY() ) );
	}

	if ( X() < 0) {
		velocityX( abs( velocityX() ) );
		status=0;
	}
	if ( X() > worldWidth-frameWidth) {
		velocityX( -abs( velocityX() ) );
		status= 1;
	}

	if (abs(X()-lastXPos)> abs(velocityX()/paceLength)){
		lastXPos= X();
		frameOffset = 1 + status* 5;
		currentFrame = (currentFrame+1 - frameOffset)%5+ frameOffset;
	}
}


