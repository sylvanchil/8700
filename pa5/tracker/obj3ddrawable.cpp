#include "obj3ddrawable.h"
#include "ioManager.h"
#include "viewpoint.h"
#include <cmath>
#include "aaline.h"
#include "matrix.h"

void Obj3DDrawable::draw()const{
	//todo
	Point3d p = Viewpoint::getInstance().point3DinView(getPosition());
	if(p.z > 100){
	
	const Uint32 BLACK= SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);

	for(std::vector<Line2d>::const_iterator i = projectedLines.begin(); i != projectedLines.end(); i ++){
		Draw_AALine(screen, round(screen->w/2- (*i).p1.x),round(screen->h/2-(*i).p1.y), round(screen->w/2-(*i).p2.x), round(screen->h/2-(*i).p2.y) , 0.1, BLACK);
	}

}
}

void Obj3DDrawable::update(Uint32 ticks){
	//todo

	// 	setPosition(getPosition((double)ticks/10*getVelocity() ));

	setPosition(
			Point3d(X()+VX()/1000*ticks, Y()+VY()/1000*ticks, Z()+VZ()/1000*ticks )
			);

	double delterX = VX()/1000*ticks;
	double delterY = VY()/1000*ticks;
	double delterZ = VZ()/1000*ticks;


	for(std::vector<Line3d>::iterator i = lines.begin(); i != lines.end();i  ++){
		(*i).p1.x+= delterX;
		(*i).p1.y+= delterY;
		(*i).p1.z+= delterZ;

		(*i).p2.x+= delterX;
		(*i).p2.y+= delterY;
		(*i).p2.z+= delterZ;
	}


	//	updateProjectedLines();

	///	std::cout << Z() << std::endl;
	//	std::cout << VZ()<< std::endl;
	//
	ticks = ticks;//delete this line
}


void Obj3DDrawable::rotate(char axis, double angle){
	double cosTheta = cos(angle);
	double sinTheta = sin(angle);

	double shiftToCenter[16]= {
		1,0,0,X(),
		0,1,0,Y(),
		0,0,1,Z(),
		0,0,0,1
	};


	double shiftBack[16]= {
		1,0,0,-X(),
		0,1,0,-Y(),
		0,0,1,-Z(),
		0,0,0,1
	};
	
	Matrix STCMatrix(4,4,shiftToCenter);
	Matrix SBMatrix(4,4, shiftBack);


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

	STCMatrix= STCMatrix* spinMatrix;
	STCMatrix = STCMatrix* SBMatrix;
	//	double posiVectorData[4]={0,0,0,1};
	//	Matrix posiVector(1,4, posiVectorData);

	for(unsigned int i = 0;i != lines.size(); i ++){
		double p1Posi[] = {
			lines[i].p1.x, 	
			lines[i].p1.y, 	
			lines[i].p1.z,
			1};
		Matrix p1PosiVector(1,4, p1Posi);
		p1PosiVector= STCMatrix*p1PosiVector;
		lines[i].p1.x= p1PosiVector.dataAt(0,0);
		lines[i].p1.y= p1PosiVector.dataAt(0,1);
		lines[i].p1.z= p1PosiVector.dataAt(0,2);


		double p2Posi[] = {
			lines[i].p2.x, 	
			lines[i].p2.y, 	
			lines[i].p2.z,
			1};
		Matrix p2PosiVector(1,4, p2Posi);
		p2PosiVector= STCMatrix*p2PosiVector;
		lines[i].p2.x= p2PosiVector.dataAt(0,0);
		lines[i].p2.y= p2PosiVector.dataAt(0,1);
		lines[i].p2.z= p2PosiVector.dataAt(0,2);

	}

	double vel[]= {
		VX(),
		VY(),
		VZ(),
		1
	};
	Matrix velVec(1,4,vel);
	velVec = spinMatrix*velVec;
	VX(velVec.dataAt(0,0));
	VY(velVec.dataAt(0,1));
	VZ(velVec.dataAt(0,2));

	Point3d bu = getBU();
	double bodyuprightdata[] = {
		bu.x,
		bu.y,
		bu.z,
		1
	};
	Matrix buVec(1,4,bodyuprightdata);
	buVec = spinMatrix* buVec;
	setBU(Point3d(buVec.dataAt(0,0), buVec.dataAt(0,1), buVec.dataAt(0,2)));
	
	/*	for(std::vector<Line3d>::iterator i = lines.begin(); i != lines.end();i ++){
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
		}*/
}

void Obj3DDrawable::updateProjectedLines(){

	projectedLines.clear();
	for(std::vector<Line3d>::iterator i = lines.begin();i != lines.end();i ++){
		projectedLines.push_back(Viewpoint::getInstance().lookAtLine3D(*i));
	}


}


















