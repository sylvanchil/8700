#ifndef 3DDRAWABLE_H
#define 3DDRAWABLE_H

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

	virtual void draw() const = 0;
	virtual void update(Uint32 ticks) = 0;

private:
	std::string name;
	Point3d position;
	Point3d velocity;

	
	
};


#endif 
