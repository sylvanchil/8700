#include"paperplaneobj3ddrawable.h"

#include<cmath>

Plane3DDrawable::Plane3DDrawable(const std::string& n, const Point3d& p, const Point3d& vel):

	Obj3DDrawable(n, p, vel)
{
	Point3d A(0,0,940);
	Point3d B(0,-20,900-40);
	Point3d C(-40,0,900-40);
	Point3d D(-20,10,900-40);
	Point3d E(20,10,900-40);
	Point3d F(40,0,900-40);

	getLines().clear();
	getLines().push_back(Line3d(A, C));
	getLines().push_back(Line3d(A, D));
	getLines().push_back(Line3d(A, B));
	getLines().push_back(Line3d(A, E));
	getLines().push_back(Line3d(A, D));
	getLines().push_back(Line3d(A, F));
	getLines().push_back(Line3d(C, D));
	getLines().push_back(Line3d(D, B));
	getLines().push_back(Line3d(B, E));
	getLines().push_back(Line3d(E, F));

}

void Plane3DDrawable::update(Uint32 ticks){

	Obj3DDrawable::update(ticks);

	Obj3DDrawable::updateProjectedLines();
	
}
