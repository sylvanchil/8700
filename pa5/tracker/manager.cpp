#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "gamedata.h"
#include "manager.h"
#include "blockobj3ddrawable.h"
#include "paperplaneobj3ddrawable.h"
#include "objexplode.h"
#include "explosion.h"

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
	plane(),

	bp(),
	ep(),
	background(),
	objs(),

	makeVideo( false ),
	frameCount( 0 ),
	username(  Gamedata::getInstance().getXmlStr("username") ),
	title( Gamedata::getInstance().getXmlStr("screenTitle") ),
	frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
	godMode(false),
	updated(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw string("Unable to initialize SDL: ");
	}
	SDL_WM_SetCaption(title.c_str(), NULL);
	atexit(SDL_Quit);

	hud = new HUDObj3DDrawable(
			"hud", 
			Point3d(0,0,0),
			Point3d(0,0,0),
			Gamedata::getInstance().getXmlInt("hud/lifetime")
			);

	plane = new Plane3DDrawable("paperplane", Point3d(0,0,640), Point3d(0,0,50));

	objs.push_back(hud);
	objs.push_back(plane);

	objs.push_back(new Plane3DDrawable("paperplane", Point3d(0,0,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(10,30,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-100,100,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(700,250,2200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-800,350,600), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(30,320,500), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-100,230,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(120,330,3200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-130,430,500), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(350,530,800), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-260,630,900), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-340,130,1000), Point3d(0,0,0)));


//	objs.push_back(new Explosion("explosion,", Point3d(0,0,1300), Point3d(0,0,0)));
	//viewpoint

//		objs.push_back(new ObjExplosion(Point3d(0,0,2000), Point3d(0,0,0)));

	Viewpoint::getInstance().setObjToTrack(plane);
}

void Manager::reset(){

	delete hud;
	hud = new HUDObj3DDrawable(
			"hud", 
			Point3d(0,0,0),
			Point3d(0,0,0),
			Gamedata::getInstance().getXmlInt("hud/lifetime")
			);

	delete plane;
	plane = new Plane3DDrawable("paperplane", Point3d(0,0,640), Point3d(0,0,50));
	/*	
		std::list<Drawable3D*>::iterator i = objs.begin();
		i ++;
		i++;
		while(i != objs.end()){
		delete *i;
		}
	 */
	objs.clear();

	objs.push_back(hud);
	objs.push_back(plane);



	objs.push_back(new Plane3DDrawable("paperplane", Point3d(0,0,1200), Point3d(0,0,0)));

	objs.push_back(new Plane3DDrawable("paperplane", Point3d(10,30,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-100,100,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(700,250,2200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-800,350,600), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(30,320,500), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-100,230,1200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(120,330,3200), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-130,430,500), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(350,530,800), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-260,630,900), Point3d(0,0,0)));
	objs.push_back(new Plane3DDrawable("paperplane", Point3d(-340,130,1000), Point3d(0,0,0)));


	//viewpoint

	Viewpoint::getInstance().setObjToTrack(plane);

	bp = BulletPool();

}


void Manager::collisionDetect(){
std::list<Drawable3D*>::iterator obji= objs.begin();
	while(obji != objs.end()){
		if(*obji != hud && *obji != plane){
	
			if((*obji)->collidedWith(plane)){
				if(!godMode){
				std::cout << "collided with plane" << std::endl;
			}}
		
			for(std::list<Bullet*>::iterator bulleti = bp.getBulletList().begin();
					bulleti != bp.getBulletList().end(); 
					bulleti ++
			   ){
				if((*obji)->collidedWith(*bulleti)){
				//	objs.push_back(new ObjExplosion(*obji));
					ep.explode((*obji)->getPosition(), (*obji)->getVelocity());
					delete (*obji);
					objs.remove(*obji);
					obji--;

				}
			}

//			if((*obji)->collidedWith(plane)){
//				if(!godMode){
//				std::cout << "collided with plane" << std::endl;
//			}}
		}
		obji ++;



	}
/*	for(std::list<Drawable3D*>::iterator obji= objs.begin(); obji != objs.end();obji ++){
		if(*obji != hud && *obji != plane){
			for(std::list<Bullet*>::iterator bulleti = bp.getBulletList().begin();
					bulleti != bp.getBulletList().end(); 
					bulleti ++
			   ){
				if((*obji)->collidedWith(*bulleti)){
					objs.remove(*obji);
					std::cout << "collided" << std::endl;
				}

			}

			if((*obji)->collidedWith(plane)){
				std::cout << "collided with plane" << std::endl;
			}
		}


	}*/
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

	bp.draw();
	ep.draw();
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
		Viewpoint::getInstance().update();

		bp.update(ticks);
		ep.update(ticks);
		updated = true;

	}

	hud->setBullet(bp.bulletSize());
	hud->setFreebullet(bp.freeSize());

	collisionDetect();

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
				if(keystate[SDLK_g]){
					godMode= !godMode;
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

				if(keystate[SDLK_SPACE]){
					std::cout << "shoot \n";
					bp.shoot(plane->getPosition(), plane->getVelocity());
				}

				if(keystate[SDLK_r]){
					reset();
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
				plane->rotate('x', 0.00005);
			}

			if(keystate[SDLK_s]){
				plane->rotate('x', -0.00005);
			}

			if(keystate[SDLK_a]){
				plane->rotate('z', -0.00005);
			}

			if(keystate[SDLK_d]){
				plane->rotate('z', 0.00005);
			}
		}



		if(updated){	
			draw();
		}
		update();
	}
}
