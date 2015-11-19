#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
	std::list<Drawable*>::const_iterator ptr = sprites.begin();
	while ( ptr != sprites.end() ) {
		delete (*ptr);
		++ptr;
	}
}

Manager::Manager() :
	env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	io( IOManager::getInstance() ),
	clock( Clock::getInstance() ),
	screen( io.getScreen() ),
	
	background(),
	sprites(),

	makeVideo( false ),
	frameCount( 0 ),
	username(  Gamedata::getInstance().getXmlStr("username") ),
	title( Gamedata::getInstance().getXmlStr("screenTitle") ),
	frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
	updated(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw string("Unable to initialize SDL: ");
	}
	SDL_WM_SetCaption(title.c_str(), NULL);
	atexit(SDL_Quit);

	

//	sprites.push_back( new MultiSprite("matchman") );
	
	//add sprite 
//	sprites.push_back(new Background());

	//viewpoint


}

void Manager::draw() const {

	background.draw();

	clock.draw();
	std::list<Drawable*>::const_iterator ptr = sprites.begin();
	while ( ptr != sprites.end() ) {
		(*ptr)->draw();
		++ptr;
	}

	SDL_Flip(screen);
}

// Move this to IOManager
void Manager::makeFrame() {
	std::stringstream strm;
	strm << "frames/" << username<< '.' 
		<< std::setfill('0') << std::setw(4) 
		<< frameCount++ << ".bmp";
	std::string filename( strm.str() );
	std::cout << "Making frame: " << filename << std::endl;
	SDL_SaveBMP(screen, filename.c_str());
}


void Manager::update() {
	clock.update();
	Uint32 ticks = clock.getTicksSinceLastFrame();

	if (ticks == 0){
		updated = false;
	}
	else {

		std::list<Drawable*>::const_iterator ptr = sprites.begin();
		while ( ptr != sprites.end() ) {
			(*ptr)->update(ticks);
			++ptr;
		}
		if ( makeVideo && frameCount < frameMax ) {
			makeFrame();
		}
		
		// viewpoint update

		updated = true;

	}

}

void Manager::play() {
	SDL_Event event;
	bool done = false;
	clock.start();

	
	//move chacter wasd
	while ( not done ) {
		while ( SDL_PollEvent(&event) ) {
			Uint8 *keystate = SDL_GetKeyState(NULL);
			if (event.type ==  SDL_QUIT) { done = true; break; }
			if(event.type == SDL_KEYDOWN) {
				if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
					done = true;
					break;
				}
				if ( keystate[SDLK_t] ) {
				
				}
				if ( keystate[SDLK_p] ) {
					if ( clock.isPaused() ) clock.unpause();
					else clock.pause();
				}
				if (keystate[SDLK_s]) {
					clock.toggleSloMo();
				}
				if (keystate[SDLK_F4] && !makeVideo) {
					std::cout << "Making video frames" << std::endl;
					makeVideo = true;
				}
				// F1 to triger hud
				if(keystate[SDLK_F1]){
				
				
				}	

			}
		}
		if(updated){	
			draw();
		}
		update();
	}
}
