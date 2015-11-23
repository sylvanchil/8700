#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "gamedata.h"
#include "manager.h"
#include "blockobj3ddrawable.h"
#include "paperplaneobj3ddrawable.h"


Manager::~Manager() { 
	std::list<Drawable3D*>::const_iterator ptr = objs.begin();
	while ( ptr != objs.end() ) {
		delete (*ptr);
		++ptr;
	}
}

Manager::Manager() :
	env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
	io( IOManager::getInstance() ),
	clock( Clock::getInstance() ),
	screen( io.getScreen() ),

	block(),
	ground(),
	hud(),

	background(),
	objs(),

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


	ground=	new Ground3DDrawable("ground",
			Point3d(
				Gamedata::getInstance().getXmlFloat("ground/posiX"),
				Gamedata::getInstance().getXmlFloat("ground/posiY"),
				Gamedata::getInstance().getXmlFloat("ground/posiZ")
				), 
			Point3d(0,0,0),
			Gamedata::getInstance().getXmlInt("ground/width"),
			Gamedata::getInstance().getXmlInt("ground/length"),
			Gamedata::getInstance().getXmlInt("ground/lineDistance")
			);	


	//todo
	block= 		new Block3DDrawable(
			"cube",
			Point3d(
				Gamedata::getInstance().getXmlFloat("block/posiX"),
				Gamedata::getInstance().getXmlFloat("block/posiY"),
				Gamedata::getInstance().getXmlFloat("block/posiZ")
				),
			Point3d(
				Gamedata::getInstance().getXmlFloat("block/velX"),
				Gamedata::getInstance().getXmlFloat("block/velY"),
				Gamedata::getInstance().getXmlFloat("block/velZ")

				),
			Point3d(
				Gamedata::getInstance().getXmlFloat("block/dimX"),
				Gamedata::getInstance().getXmlFloat("block/dimY"),
				Gamedata::getInstance().getXmlFloat("block/dimZ")

				),
			Gamedata::getInstance().getXmlFloat("block/topspeed"),
			//			Gamedata::getInstance().getXmlFloat("block/topbackspeed"),
			Gamedata::getInstance().getXmlFloat("block/acceleration")

				);

	hud = new HUDObj3DDrawable(
			"hud", 
			Point3d(0,0,0),
			Point3d(0,0,0),
			Gamedata::getInstance().getXmlInt("hud/lifetime")
			);

//	objs.push_back(ground);
	objs.push_back(block);
	objs.push_back(hud);
	objs.push_back(new Plane3DDrawable(
		"paperplane",
		Point3d(0,0,800),
		Point3d(0,0,0)
	));

	//	sprites.push_back( new MultiSprite("matchman") );

	//add sprite 
	//	sprites.push_back(new Background());

	//viewpoint


}

void Manager::draw() const {

	hud->setSecond(clock.getSeconds());
	hud->setFPS(clock.getFps());
	background.draw();

	//	clock.draw();
	std::list<Drawable3D*>::const_iterator ptr = objs.begin();
	while ( ptr !=objs.end() ) {
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

		std::list<Drawable3D*>::const_iterator ptr = objs.begin();
		while ( ptr != objs.end() ) {
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
		while(SDL_PollEvent(&event)){
			Uint8 *keystate = SDL_GetKeyState(NULL);
			if(event.type == SDL_KEYDOWN) {

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

					hud->renewLifeTime();

				}	

				if(keystate[SDLK_m]){
					//trigger minimap
				}


			}		

		}


		SDL_PollEvent(&event) ; 
		Uint8 *keystate = SDL_GetKeyState(NULL);
		if (event.type ==  SDL_QUIT) { done = true; break; }
		if(event.type == SDL_KEYDOWN) {
			if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
				done = true;
				break;
			}

			if(keystate[SDLK_w]){
				block->moveNorth();
				//	block->accelerate();
			}
			if(keystate[SDLK_s]){
				block ->moveSouth();
				//			block->goback();
			}

			if(keystate[SDLK_a]){

				block->moveEast();
				//	block->turnLeft();
			}

			if(keystate[SDLK_d]){

				block->moveWest();
				//	block->turnRight();
			}

			if(keystate[SDLK_u]){
				block->rotate('x', 0.0001);
			}
			if(keystate[SDLK_j]){
				block->rotate('y', 0.0001);
			}
			if(keystate[SDLK_k]){
				block->rotate('z', 0.0001);
			}

		}



		if(updated){	
			draw();
		}
		update();
	}
}
