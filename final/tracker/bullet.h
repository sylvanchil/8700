#ifndef BULLET_H
#define BULLET_H
#include "obj3ddrawable.h"
#include "viewpoint.h"

class Bullet:public Obj3DDrawable{
public:
	Bullet(const std::string& n, Point3d pos, Point3d vel):
	Obj3DDrawable(n, pos, vel),
	livetime(10000)
	{
		setColor(  SDL_MapRGB(getScreen()->format, 0xff, 0x00, 0x00));
		getLines().push_back(Line3d(Point3d(X()-VX()/3, Y()-VY()/3,Z()-VZ()/3), getPosition()));
	}

	void set(Point3d pos,Point3d vel, int lt){
		setPosition(pos);
		setVelocity(vel);
		livetime = lt;
	}

	void draw()const {

		Obj3DDrawable::draw();
	}

	void update(Uint32 ticks){
		Obj3DDrawable::update(ticks);
		
		Obj3DDrawable::updateProjectedLines();
		livetime-=ticks;
//		std::cout << livetime << std::endl;
	}

	bool alive(){return livetime>0;}

private:
	int livetime;

};

#endif 
