#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"
#include <cstdlib>
#include<cstring>
#include<cstdio>


using std::string;
using std::stringstream;

Clock& Clock::getInstance() {
	if ( SDL_WasInit(SDL_INIT_VIDEO) == 0) {
		throw std::string("Must init SDL before Clock");
	}
	static Clock clock; 
	return clock;
}

Clock::Clock() :
	ticks(0),
	started(false), 
	paused(false), 
	sloMo(false), 
	ticksAfter(SDL_GetTicks()),
	ticksBefore(SDL_GetTicks()),
	uptimeTicks(0)
{
	start();
}

Clock::Clock(const Clock& c) :
	ticks(c.ticks), 
	started(c.started), 
	paused(c.paused), 
	sloMo(c.sloMo), 
	ticksAfter(c.ticksAfter),
	ticksBefore(c.ticksBefore),
	uptimeTicks(c.uptimeTicks)	
{
	start();
}

void Clock::draw() const {

	//construct string like "FPS: 1000"
	stringstream ss;
	ss << getFps();
	std::string fpsStr("FPS: ");
	fpsStr+=ss.str();
	IOManager::getInstance().printMessageAt(fpsStr, 10, 30);
	
	//construct string like "Time: 10"
	ss.str("");
	ss<< (uptimeTicks)/1000;
	std::string str("Time: ");
	str+=ss.str();
	IOManager::getInstance().printMessageAt(str,10,10);

}

void Clock::update() { 
	ticksBefore = ticksAfter;
	ticksAfter = SDL_GetTicks();
	ticks=ticksAfter-ticksBefore;
	uptimeTicks += ticks;
	if(sloMo){
		ticks=ticks/2;
	}
	if(paused){
		//if paused, compensate the tick
		uptimeTicks -= ticks;
		uptimeTicks+=0;
		ticks =0;
	}

}

unsigned int Clock::getTicksSinceLastFrame() const {
	return ticks;
}

void Clock::toggleSloMo() {
	sloMo = !sloMo;
}

int Clock::getFps() const {
	if(ticks!=0)
		return (int)(1000/ticks);
	else
		return 1;
}

void Clock::start() { 
	started = true; 
	paused = false; 
}

void Clock::pause() { 
	paused = !paused;
}

void Clock::unpause() { 
	paused= !paused;
}

