#include "obj3ddrawable.h"
#include "ioManager.h"
#include "viewpoint.h"
#include <cmath>
#include "aaline.h"
#include "matrix.h"

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


void Obj3DDrawable::rotate(char axis, double angle){
	double cosTheta = cos(angle);
	double sinTheta = sin(angle);



	double spin[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	switch(axis){
	case 'x':
		spin[5] = cosTheta;
		spin[6] = -sinTheta;
		spin[9] = sinTheta;
		spin[10] = cosTheta;
		break;
	case 'y':
		spin[0] = cosTheta;
		spin[2] = -sinTheta;
		spin[8] = sinTheta;
		spin[10] = cosTheta;
		break;
	case 'z':
		spin[0] = cosTheta;
		spin[1] = -sinTheta;
		spin[4] = sinTheta;
		spin[5] = cosTheta;
		break;
	default:
		break;
	}

	Matrix spinMatrix(4,4,spin);

	double posiVectorData[4]={0,0,0,1};
	Matrix posiVector(1,4, posiVectorData);

	for(std::vector<Line3d>::iterator i = lines.begin(); i != lines.end();i ++){
		posiVector.setDataAt(0,0, (*i).p1.x);
		posiVector.setDataAt(0,1, (*i).p1.y);
		posiVector.setDataAt(0,2, (*i).p1.z);
		posiVector.setDataAt(0,3, 1);
		posiVector= spinMatrix*posiVector;
		(*i).p1.x = posiVector.dataAt(0,0);
		(*i).p1.y = posiVector.dataAt(0,1);
		(*i).p1.z = posiVector.dataAt(0,2);
	
		posiVector.setDataAt(0,0, (*i).p2.x);
		posiVector.setDataAt(0,1, (*i).p2.y);
		posiVector.setDataAt(0,2, (*i).p2.z);
		posiVector.setDataAt(0,3, 1);
		posiVector= spinMatrix*posiVector;
		(*i).p2.x = posiVector.dataAt(0,0);
		(*i).p2.y = posiVector.dataAt(0,1);
		(*i).p2.z = posiVector.dataAt(0,2);
	
	}
	
}




















