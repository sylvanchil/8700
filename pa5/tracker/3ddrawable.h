#ifndef _3DDRAWABLE_H
#define _3DDRAWABLE_H

#include<string>
#include<SDL.h>
#include<iostream>
#include"geo.h"

class Drawable3D {

public:
	Drawable3D(const std::string& n, const Point3d& pos, const Point3d& vel):
		name(n), position(pos), velocity(vel),bodyUpright(Point3d(0,1,0)){
	}

	virtual ~Drawable3D(){}

	const std::string& getName()const{return name;}
	void setName(const std::string& n) {name = n;}

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks) = 0;

	double X()const {return position.x;}
	double Y()const {return position.y;}
	double Z()const {return position.z;}

	Point3d getPosition()const{return position;}

	void X(double x){position.x= x;}
	void Y(double y){position.y= y;}
	void Z(double z){position.z= z;}
	
	void setPosition(Point3d p){position = p;}

	double VX()const {return velocity.x;}
	double VY()const {return velocity.y;}
	double VZ()const {return velocity.z;}
	
	Point3d getVelocity(){return velocity;}

	void VX(double x){velocity.x= x;}
	void VY(double y){velocity.y= y;}
	void VZ(double z){velocity.z= z;}

	void setVelocity(Point3d v){velocity = v;}

	Point3d getBU(){return bodyUpright;}
	void setBU(Point3d b){bodyUpright = b;}

	virtual bool collidedWith(const Drawable3D* d){
		return position.distanceTo(d->getPosition())< 20;	
	}
	

private:
	std::string name;
	Point3d position;
	Point3d velocity;
	Point3d bodyUpright;

};

#endif 
