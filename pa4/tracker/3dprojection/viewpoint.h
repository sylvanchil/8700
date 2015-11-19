#ifndef _VIEWPOINT_H_
#define _VIEWPOINT_H_

#include"geo.h"
#include"matrix.h"
class Viewpoint{
public:
	Point3d position;
	Point3d direction;

	double screenDistance;

	Point2d lookAt3dPoint(const Point3d& p3d);
	
	Line2d lookAt3dLine(const Line3d& l3d);

	Viewpoint():
		position(Point3d(0,0,0)),
		direction(Point3d(0,0,1)),
		screenDistance(320){}
	
	Viewpoint(double sD):
		position(Point3d(0,0,0)),
		direction(Point3d(0,0,1)),
		screenDistance(sD){}
		
	Viewpoint(Point3d p,double sD):
		position(p),
		direction(Point3d(0,0,1)),
		screenDistance(sD){}
	
	Viewpoint(Point3d p,Point3d d):
		position(p),
		direction(d),
		screenDistance(320){}

	Viewpoint(Point3d p,Point3d d,double sD):
		position(p),
		direction(d),
		screenDistance(sD){}

private:
	Point3d point3dInView(const Point3d& p3d);

};


#endif
