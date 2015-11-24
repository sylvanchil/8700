#include"paperplaneobj3ddrawable.h"

#include<cmath>

Plane3DDrawable::Plane3DDrawable(const std::string& n, const Point3d& p, const Point3d& vel):

	Obj3DDrawable(n, p, vel)
{
	Point3d A(X()+0,Y()+0,Z()+40);
	Point3d B(X()+0,Y()-20,Z()-40);
	Point3d C(X()-40,Y()+0,Z()-40);
	Point3d D(X()-20,Y()+10,Z()-40);
	Point3d E(X()+20,Y()+10,Z()-40);
	Point3d F(X()+40,Y()+0,Z()-40);

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
