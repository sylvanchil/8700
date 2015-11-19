// Brian Malloy        March, 2014

#include <cmath>  // for sqrtf
#include <iostream>
#include "ioManager.h"
#include "aaline.h"
#include "viewpoint.h"
#include "matrix.h"
#include "geo.h"
#include <vector>

IOManager *IOManager::instance = NULL;

void drawBackground(SDL_Surface* screen) {
	SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
	SDL_Rect dest = {0, 0, 0, 0};
	SDL_BlitSurface( screen, NULL, screen, &dest );
}

void play() {


	Point3d vpPosi(0, 320, 0);
	Point3d vpDirec(0,0,1);
	Viewpoint vp(vpPosi,vpDirec);


	std::vector<Line3d> vL3d;
	std::vector<Line2d> vL2d;

	for(int x = -640; x <641; x +=40){
		vL3d.push_back(Line3d(Point3d(x, 0, 320), Point3d(x, 0, 1600)));
	}

	for(int z = 320; z < 1601; z += 40){
		vL3d.push_back(Line3d(Point3d(-640,0,z), Point3d(640, 0, z)));
	}

	for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
		vL2d. push_back(vp. lookAt3dLine(*i));
	}


	SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"));
	IOManager* io = IOManager::getInstance();
	SDL_Surface * const screen = io->getScreen();
	const Uint32 BLACK= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	atexit(SDL_Quit);

	SDL_Event event;
	bool done = false;
	while ( not done ) {
		drawBackground(screen);
		Uint8 *keystate = SDL_GetKeyState(NULL);
		SDL_PollEvent(&event); 
			switch (event.type) {
				case SDL_QUIT: {
								   done = true;
								   break;
							   }
				case SDL_KEYDOWN: 
							   {
								   if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
									   done = true;
									   break;
								   }
								   if(keystate[SDLK_a]){
									   vp.direction.x+=0.001;			  
									   //							  std::cout <<vp.direction.x << std::endl;

									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }


									   break;
								   }	
								   if(keystate[SDLK_d]){
									   vp.direction.x-=0.001;			  
									   //							   std::cout <<vp.direction.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	

								   if(keystate[SDLK_w]){
									   vp.direction.y+=0.001;			  
									   //							   std::cout <<vp.direction.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	
								   if(keystate[SDLK_s]){
									   vp.direction.y-=0.001;			  
									   //							   std::cout <<vp.direction.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	

								   if(keystate[SDLK_u]){
									   vp.position.z+=10;			  
									   //							   std::cout <<vp.position.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	if(keystate[SDLK_j]){
									   vp.position.z-=10;			  
									   //							   std::cout <<vp.position.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	
								   if(keystate[SDLK_UP]){
									   vp.position.y+=10;			  
									   //							   std::cout <<vp.position.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	if(keystate[SDLK_DOWN]){
									   vp.position.y-=10;			  
									   //							   std::cout <<vp.position.x << std::endl;
									   vL2d.clear();
									   for(std::vector<Line3d>::iterator i = vL3d.begin();i != vL3d.end();i ++){
										   vL2d. push_back(vp. lookAt3dLine(*i));
									   }

									   break;
								   }	
							   }
			}

		for(std::vector<Line2d>::iterator i = vL2d.begin(); i != vL2d.end(); i ++){
			Draw_AALine(screen, round(620-320 - (*i).p1.x),round(240-(*i).p1.y), round(320-(*i).p2.x), round(240-(*i).p2.y) , 0.1, BLACK);

		}

		//		Draw_AALine(screen,  640-p2d3.x-320, 480- p2d3.y-240,  640-p2d4.x-320, 480- p2d4.y-240, BLACK);	

		SDL_Flip(screen);
	}
	delete io;
}

int main() {
	try {
		play();
	}
	catch (const string& msg) { std::cout << msg << std::endl; }
	catch (...) {
		std::cout << "Oops, someone threw an exception!" << std::endl;
	}
	return 0;
}
