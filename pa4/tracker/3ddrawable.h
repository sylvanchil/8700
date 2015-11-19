#ifndef _3DDRAWABLE_H
#define _3DDRAWABLE_H

#include<string>
#include<SDL.h>
#include<iostream>
#include"3dprojection/geo.h"

class Drawable3D {

public:
	Drawable3D(const std::string& n, const Point3d& pos, const Point3d& vel):
		name(n), position(pos), velocity(vel){
	}

	virtual ~Drawable3D(){}

	const std::string& getName()const{return name;}
	void setName(const std::string& n) {name = n;}

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks) = 0;

	double X(){return position.x;}
	double Y(){return position.y;}
	double Z(){return position.z;}
	
	void X(double x){position.x= x;}
	void Y(double y){position.y= y;}
	void Z(double z){position.z= z;}

	double VX(){return velocity.x;}
	double VY(){return velocity.y;}
	double VZ(){return velocity.z;}
	
	void VX(double x){velocity.x= x;}
	void VY(double y){velocity.y= y;}
	void VZ(double z){velocity.z= z;}

	virtual bool collidedWith(const Drawable3D* )const{
		throw std::string("No collision implemented;");
	}
	

private:
	std::string name;
	Point3d position;
	Point3d velocity;

};

#endif 
