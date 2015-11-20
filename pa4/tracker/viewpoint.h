#ifndef _VIEWPOINT_
#define _VIEWPOINT_

#include"geo.h"
#include"3ddrawable.h"
#include"gamedata.h"


class Viewpoint{

public:
	static Viewpoint& getInstance();
	void draw()const;
	void update();
	
	Point2d lookAtPoint3D(const Point3d& p);
	Line2d lookAtLine3D(const Line3d& l);

	double X(){return position.x;};
	double Y(){return position.y;};
	double Z(){return position.z;};

	void X(double x){position.x = x;};
	void Y(double y){position.y = y;};
	void Z(double z){position.z = z;};

	const Drawable3D* getObjToTrack(){return objToTrack;}
	void setObjToTrack(const Drawable3D* d3dptr ){ objToTrack = d3dptr;}

private:
	const Gamedata& data;
	
	Point3d position;
	Point3d direction;

	//Point3D relate position to obj


	double screenDistance;

	const Drawable3D* objToTrack;

	Point3d point3DinView(const Point3d& p3d);

	Viewpoint();
	Viewpoint(const Viewpoint&);
	Viewpoint& operator=(const Viewpoint&);

};

#endif
