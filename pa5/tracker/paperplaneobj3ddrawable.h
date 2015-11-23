#ifndef _PLANE_H_
#define _PLANE_H_
#include "obj3ddrawable.h"

class Plane3DDrawable: public Obj3DDrawable{
public:
	Plane3DDrawable(const std::string& n, const Point3d& p, const Point3d& v);
	void update(Uint32 ticks);
};

#endif
