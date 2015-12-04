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
		projectedLines(std::vector<Line2d>()),
		color( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00))
		{

			
		}

	Obj3DDrawable(const std::string& n, const Point3d& pos, const Point3d& vel, const std::vector<Line3d> l):
		Drawable3D(n,pos, vel),
		screen(IOManager::getInstance().getScreen()),
		lines(l),
		projectedLines(std::vector<Line2d>()),

		color( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00))
		{}


	Obj3DDrawable(const Obj3DDrawable& o3d):
	Drawable3D(o3d),

		screen(IOManager::getInstance().getScreen()),
		lines(o3d.lines),
		projectedLines(o3d.projectedLines),

		color( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00))
	{
	//todo 
	}
	Obj3DDrawable& operator=(const Obj3DDrawable& o3d){
	//todo
		screen= o3d.screen;
		lines= o3d.lines;
		projectedLines= o3d.projectedLines;
		color = o3d.color;
		return *this;
	}

	std::vector<Line3d>& getLines(){return lines;}
	std::vector<Line2d>& getProjectedLines(){return projectedLines;}

	void setColor(Uint32 c){ color = c;}
	
	SDL_Surface* getScreen()const {
	return screen;
	}

	void rotate(char direction, double angle);

	void updateProjectedLines();
	void draw() const;
	virtual	void update(Uint32 ticks);
	
private:
	SDL_Surface* screen;
	std::vector<Line3d> lines;	
	std::vector<Line2d> projectedLines;
	Uint32 color;	

};


#endif
