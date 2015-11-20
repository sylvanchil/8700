#include "obj3ddrawable.h"
#include "ioManager.h"
#include "viewpoint.h"
#include <cmath>
#include "aaline.h"

void Obj3DDrawable::draw()const{
//todo
	
	const Uint32 BLACK= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	for(std::vector<Line2d>::const_iterator i = projectedLines.begin(); i != projectedLines.end(); i ++){
		Draw_AALine(screen, round(screen->w/2- (*i).p1.x),round(screen->h/2-(*i).p1.y), round(screen->w/2-(*i).p2.x), round(screen->h/2-(*i).p2.y) , 0.1, BLACK);
	}

}

void Obj3DDrawable::update(Uint32 ticks){
//todo

// 	setPosition(getPosition((double)ticks/10*getVelocity() ));

	setPosition(
		Point3d(X()+VX()/1000*ticks, Y()+VY()/1000*ticks, Z()+VZ()/1000*ticks )
	);

///	std::cout << Z() << std::endl;
//	std::cout << VZ()<< std::endl;
//

	ticks = ticks;//delete this line

	projectedLines.clear();
	for(std::vector<Line3d>::iterator i = lines.begin();i != lines.end();i ++){
		projectedLines. push_back(Viewpoint::getInstance().lookAtLine3D(*i));
	}

}
