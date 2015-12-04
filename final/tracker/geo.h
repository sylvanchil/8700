#ifndef _GEO_H_
#define _GEO_H_

#include<cmath>

class Point2d{
	public:
		double x;
		double y;

		Point2d():x(0), y(0){

		}
		Point2d(double a, double b):x(a), y(b){

		}
		Point2d(const Point2d& p):x(p.x), y(p.y){

		}
		Point2d& operator = (const Point2d& p){
			x= p.x;
			y = p.y;
			return *this ;
		}
};

class Point3d{
	public:
		double x;
		double y;
		double z;

		Point3d():
			x(0), y(0), z(0){

			}
		Point3d(double ix,double iy, double iz):
			x(ix),y(iy),z(iz){
			}

		Point3d(const Point3d & p)
			:		x(p.x), y (p.y), z(p.z)
		{}

		double distanceTo(const Point3d& p2){
			return sqrt(pow(x-p2.x, 2)+ pow(y - p2.y, 2)+ pow(z - p2.z,2));
		}
};


class Line2d{
	public :
		Point2d p1;
		Point2d p2;
		Line2d():
			p1(Point2d(0.0,0.0)),
			p2(Point2d(0.0,0.0)){}

		Line2d(double x1, double y1, double x2, double y2):
			p1(Point2d(x1, y1)),
			p2(Point2d(x2, y2)){}

		Line2d(Point2d p2d1, Point2d p2d2):
			p1(p2d1), p2(p2d2){}

		Line2d(const Line2d& l):
			p1(l.p1),
			p2(l.p2){}

};

class Line3d{
	public :
		Point3d p1;
		Point3d p2;

		Line3d():
			p1(Point3d(0.0,0.0,0.0)),
			p2(Point3d(0.0,0.0,0.0)){}

		Line3d(double x1, double y1, double z1, double x2, double y2, double z2):
			p1(Point3d(x1, y1, z1)),
			p2(Point3d(x2, y2, z2)){}

		Line3d(Point3d p3d1, Point3d p3d2):
			p1(p3d1), p2(p3d2){}

		Line3d(const Line3d& l):
			p1(l.p1),
			p2(l.p2){}

};


#endif
