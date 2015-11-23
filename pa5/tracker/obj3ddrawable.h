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
	Drawable3D(o3d),

		screen(IOManager::getInstance().getScreen()),
		lines(o3d.lines),
		projectedLines(o3d.projectedLines)
	{
	//todo 
	}
	Obj3DDrawable& operator=(const Obj3DDrawable& o3d){
	//todo
		screen= o3d.screen;
		lines= o3d.lines;
		projectedLines= o3d.projectedLines;
		return *this;
	}

	std::vector<Line3d>& getLines(){return lines;}
	std::vector<Line2d>& getProjectedLines(){return projectedLines;}
	
	SDL_Surface* getScreen(){
	return screen;
	}

	void rotate(char direction, double angle);

	void draw() const;
	virtual	void update(Uint32 ticks);
	
private:
	SDL_Surface* screen;
	std::vector<Line3d> lines;	
	std::vector<Line2d> projectedLines;
	

};


#endif
