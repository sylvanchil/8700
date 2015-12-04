#ifndef _PLANE_H_
#define _PLANE_H_
#include "obj3ddrawable.h"

class Plane3DDrawable: public Obj3DDrawable{
public:
	
	Plane3DDrawable(const std::string& n, const Point3d& p, const Point3d& v);

	//to be implemented
	void noseUp();
	void rotateACW();
	void rotateCW();

	void shoot();

	void update(Uint32 ticks);
	
private:
	int cd;
	
};

#endif
