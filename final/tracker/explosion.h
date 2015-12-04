#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "obj3ddrawable.h"
#include "bullet.h"
#include <list>
#include <cmath>

class Explosion:public Obj3DDrawable{
public:
	Explosion(const std::string& n, Point3d pos, Point3d vel):
		Obj3DDrawable(n, pos, vel),
		livetime(8000),
		beams(std::list<Bullet*> ())
		{
			setColor(SDL_MapRGB(getScreen()->format, 0xff, 0x00, 0x00)  );
			for(int i = 0;i != 50; i++){
				int vx = rand()%200-100;
				int vy = rand()%200-100;
				int vz = rand()%200-100;
				beams.push_back(new Bullet(n, pos,Point3d(vx, vy, vz)) );	
			}
		std::list<Bullet*>::iterator i = beams.begin();
		int c=0;
		while(i!= beams.end()){
			c = rand()%200;
			(*i)->setColor(SDL_MapRGB(getScreen()->format, 0xff, c, 0x00));
			i++;
		}
		

		}

	void set(Point3d pos, Point3d vel, int lt){
		setPosition(pos);
		setVelocity(vel);
		livetime = lt;
		//beams;	
		int vx = 0;
		int vy = 0;
		int vz = 0;
		std::list<Bullet*>::iterator i = beams.begin();
		while(i!= beams.end()){
			vx = rand()%200-100;
			vy = rand()%200-100;
			vz = rand()%200-100;

			(*i)->set(pos, Point3d(vx, vy ,vz), 8000);			
			i++;
		}

	}

	void draw()const{
		if(alive()){
		std::list<Bullet*>::const_iterator i = beams.begin();
		while(i!= beams.end()){
			(*i)->draw();
			i++;
		}}
	}

	void update(Uint32 ticks){
		livetime -= ticks;
		if(alive()){
		std::list<Bullet*>::iterator i = beams.begin();
		while(i!= beams.end()){
			(*i)->update(ticks);
			i++;
		}
	}
	}

	bool alive()const {return livetime> 0;}

private:
	int livetime;
	std::list<Bullet*> beams;
};




#endif
