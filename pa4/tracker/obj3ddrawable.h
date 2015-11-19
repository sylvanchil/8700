#ifndef OBJ3D_H
#define OBJ3D_H

#include"3ddrawable.h"
#include "ioManager.h"
#include<vector>

class Obj3DDrawable : public Drawable3D{
public:
	
	Obj3DDrawable(const std::string& n, const Point3d& pos, const Point3d& vel):
		
		Drawable3D(n, pos, vel), 
		screen(IOManager::getInstance().getScreen()),
		lines(std::vector<Line3d>()),
		projectedLines(std::vector<Line2d>())
		{

			
		}

	Obj3DDrawable(const std::string& n, const Point3d& pos, const Point3d& vel, const std::vector<Line3d> l):
		Drawable3D(n,pos, vel),
		screen(IOManager::getInstance().getScreen()),
		lines(l),
		projectedLines(std::vector<Line2d>())
		{}


	Obj3DDrawable(const Obj3DDrawable& o3d):
	Drawable3D( o3d.getName(), Point3d(o3d.X(),o3d.Y(), o3d.Z()), Point3d(  o3d.VX(),o3d.VY(), o3d.VZ()))
	{
	}
	Obj3DDrawable& operator=(const Obj3DDrawable& o3d){
	//todo
	}

	void draw() const;
	void update(Uint32 ticks);
private:
	SDL_Surface* screen;
	std::vector<Line3d> lines;	
	std::vector<Line2d> projectedLines;
};


#endif
