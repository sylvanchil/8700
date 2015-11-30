#ifndef SPARKEL_H
#define SPARKEL_H

#include"3ddrawable.h"
#include"viewpoint.h"
#include"aaline.h"
#include"ioManager.h"
#include<string>

class Sparkle: public Drawable3D{
	public:
		Sparkle(const Point3d& pos, const Point3d& vel):
			Drawable3D(std::string("s"), pos, vel),
			screen(IOManager::getInstance().getScreen()), 
			livetime(2000)
	{

	}


		Sparkle(const Sparkle& s):
			Drawable3D(s),
			screen(IOManager::getInstance().getScreen()),
			livetime(2000)
	{}
		Sparkle& operator=(const Sparkle& s){
			Sparkle s2 = s;

			return *this;
		}
		~Sparkle(){}
		void draw()const{
//			std::cout << "sparke drawing"<< std::endl;
			if(livetime> 0){
				Point3d p = Viewpoint::getInstance().point3DinView(getPosition());
				if(p.z> 100){
					Point2d p2d = Viewpoint::getInstance().lookAtPoint3D(getPosition());
//				const Uint32 BLACK= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
					//Draw_AALine(screen, screen->w/2-p2d.x, screen->h/2-p2d.y,screen->w/2-p2d.x, screen->h/2-p2d.y, BLACK);		
					Draw_Pixel(screen, screen->w/2-p2d.x, screen->h/2-p2d.y,0,0,0,128);		

				}
			}

		}

		void update(Uint32 ticks){
			livetime-= ticks;
			if(livetime >0){
				setPosition(Point3d(
							X()-VX()*ticks/10,
							Y()-VY()*ticks/10,
							Z()-VZ()*ticks/10
							)
						);
				setVelocity(Point3d(
							VX()-0.01*VX()*VX()*ticks,
							VY()-0.01*VY()*VY()*ticks,
							VZ()-0.01*VZ()*VZ()*ticks-ticks*0.001
							)
						);

			}


		}

	private:
		SDL_Surface* screen;
		int livetime;


};


#endif

