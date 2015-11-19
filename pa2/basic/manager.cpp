#include <iostream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include <vector>


Manager::~Manager() { 
	// Manager made it, so Manager needs to delete it
	SDL_FreeSurface(orbSurface);
	SDL_FreeSurface(backGroudSurface);

	delete backGroundFrame;
	delete orbFrame;
}

Manager::Manager() :
	env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	io( IOManager::getInstance() ),
	clock( Clock::getInstance() ),
	screen( io.getScreen() ),

	backGroudSurface(io.loadAndSet(
				Gamedata::getInstance().getXmlStr("backgroundpic/file"),
				Gamedata::getInstance().getXmlBool("backgroundpic/transparency")
				)
			),
	backGroundFrame(new Frame("backgroundpic", backGroudSurface)),
	backGround("backgroundpic", backGroundFrame),

	orbSurface( io.loadAndSet(
				Gamedata::getInstance().getXmlStr("singleSparkle/file"), 
				Gamedata::getInstance().getXmlBool("singleSparkle/transparency")) ),
	orbFrame( new Frame("singleSparkle", orbSurface) ),
	//	orb("greenorb", orbFrame),
	orbs( std::vector<Sprite>() ),
	orbsOriginalState(std::vector<Sprite>()),
	rounds(0),
	makeVideo( false ),
	frameCount( 0 ),
	username(  Gamedata::getInstance().getXmlStr("username") ),
	frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
	TITLE( Gamedata::getInstance().getXmlStr("screenTitle") )
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw string("Unable to initialize SDL: ");
	}
	orbs.reserve(Gamedata::getInstance().getXmlInt("sparkleCount")*30);
	orbsOriginalState.reserve(Gamedata::getInstance().getXmlInt("sparkleCount"));
	for(int i=0;  i!= Gamedata::getInstance().getXmlInt("sparkleCount"); i ++){
		orbs.push_back(Sprite("singleSparkle", orbFrame));
		orbs[i].randomSpeed();
		orbsOriginalState.push_back(Sprite("singleSparkle", orbFrame));
		orbsOriginalState[i].randomSpeed();

	}

}


void Manager::draw()  {
	backGround.draw();
	for(unsigned int i=0; i != orbs.size(); i++ )	{
		orbs[i].draw();
	}


	clock.draw();

	IOManager::getInstance().printMessageAt(
			Gamedata::getInstance().getXmlStr("projectTitle"),
			(Gamedata::getInstance().getXmlInt("world/width"))/2-60,
			10
			);

	IOManager::getInstance().printMessageAt(
			Gamedata::getInstance().getXmlStr("username"),
			(Gamedata::getInstance().getXmlInt("world/width"))-200,
			Gamedata::getInstance().getXmlInt("world/height")-20
			);

	SDL_Flip(screen);
}

void Manager::update() {
	clock.update();
	Uint32 ticks = clock.getTicksSinceLastFrame();
	for(unsigned int i= 0; i != orbs.size();i ++){
		orbs[i].update(ticks);
		orbs[i].speedUpdate(ticks);
	}

	Uint32 uptime = clock.getTicksSinceInit();

	if(!clock.isPaused()){
		int slomotimes = 1;
		if(clock.isSloMO()){
			slomotimes = Gamedata::getInstance().getXmlInt("setting/slomotimes");
			}
		
		
		if (uptime/slomotimes/(Gamedata::getInstance().getXmlInt("setting/interval"))>rounds/slomotimes){
			rounds = uptime/(Gamedata::getInstance().getXmlInt("setting/interval"));
			int x= rand()%(Gamedata::getInstance().getXmlInt("world/width"));

			int y= rand()%(Gamedata::getInstance().getXmlInt("world/height"));

			for(unsigned int i = 0; i!= orbsOriginalState.size(); i++){

				orbsOriginalState[i].gotoPosi(x,y);

				orbs.push_back(orbsOriginalState[i]);
			}
		}
}

	//for(unsigned int i= 0; i != orbs.size();i ++){
	//		orbs2[i].update(ticks);
	//		orbs2[i].speedUpdate(ticks);
	//	}



	backGround.update(ticks);

	if ( makeVideo && frameCount < frameMax ) {
		std::stringstream strm;
		strm << "frames/" << username<< '.' 
			<< std::setfill('0') << std::setw(4) 
			<< frameCount++ << ".bmp";
		std::string filename( strm.str() );
		std::cout << "Making frame: " << filename << std::endl;
		SDL_SaveBMP(screen, filename.c_str());
	}
}

void Manager::play() {
	//union of events
	SDL_Event event;

	bool done = false;

	while ( not done ) {

		//first deal with all the event in the PollEvent
		while ( SDL_PollEvent(&event) ) {
			Uint8 *keystate = SDL_GetKeyState(NULL);
			// do with switch
			if (event.type ==  SDL_QUIT) { done = true; break; }
			if (event.type == SDL_KEYDOWN) {
				if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
					done = true;
					break;
				}

				if (keystate[SDLK_F4] && !makeVideo) {
					std::cout << "Making video frames" << std::endl;
					makeVideo = true;
				}
				if (keystate[SDLK_p] ) {
					if ( clock.isPaused() )
						clock.unpause();
					else
						clock.pause();
				}
				if(keystate[SDLK_s]){
					clock.toggleSloMo();
				}
			}
		}

		draw();
		update();
	}
}
