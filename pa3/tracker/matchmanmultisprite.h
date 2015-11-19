#ifndef MATCHMANMULTISPRITE__H
#define MATCHMANMULTISPRITE__H
#include <string>
#include <vector>
#include "multisprite.h"

class MatchmanMultiSprite: public MultiSprite{
public:
	MatchmanMultiSprite(const std::string&);
//	virtual void draw()const;
	virtual void update(Uint32 ticks);
//	virtual void advanceFrame(Uint32 ticks);
	
private:
	int status;
	int frameOffset;	
	int lastXPos;
	int paceLength;
};
#endif


