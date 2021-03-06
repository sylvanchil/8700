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

	Point3d point3DinView(const Point3d& p3d);
	double X(){return position.x;}
	double Y(){return position.y;}
	double Z(){return position.z;}

	void X(double x){position.x = x;}
	void Y(double y){position.y = y;}
	void Z(double z){position.z = z;}

	double DX(){return direction.x;}
	double DY(){return direction.y;}
	double DZ(){return direction.z;}

	void DX(double x){direction.x = x;}
	void DY(double y){direction.y = y;}
	void DZ(double z){direction.z = z;}

	const Drawable3D* getObjToTrack(){return objToTrack;}
	void setObjToTrack(const Drawable3D* d3dptr ){ objToTrack = d3dptr;}
	
	double getScreenDistance(){return screenDistance;}
	void setSD(double sd){screenDistance = sd;}
	

private:
	const Gamedata& data;
	
	Point3d position;
	Point3d direction;
	Point3d bodyU;
	//Point3D relate position to obj


	double screenDistance;

	const Drawable3D* objToTrack;


	Viewpoint();
	Viewpoint(const Viewpoint&);
	Viewpoint& operator=(const Viewpoint&);

};

#endif
