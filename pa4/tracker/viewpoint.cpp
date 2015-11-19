#include"viewpoint.h"

static Viewpoint& getInstance(){
	static Viewpoint vp;
	return vp;
}

Viewpoint::Viewpoint():
	data(Gamedata::getInstance()),
	position(0,0,0), 
	direction(0,0,1),
	screenDistance(data.getXmlFloat("view/screenDistance")),
	objToTrack(NULL){

	}

Point2d Viewpoint::lookAtPoint3D( const Point3d& p3d){
	Point3d mp3d = point3DInView(p3d);
	return Point2d(screenDistance*mp3d.x/mp3d.z, screenDistance*mp3d.y/ mp3d.z);
}

Point3d point3DinView(const Point3d& p3d){
	double posi[] = {p3d.x, p3d.y, p3d.z, 1};
	Matrix posiVector(1, 4, posi);
	//fill in the matrix
	//fit the position	
	double trans[] = {
		1,0,0,-position.x,
		0,1,0,-position.y,
		0,0,1,-position.z,
		0,0,0,1
	};
	Matrix transMatrix(4,4,trans);
	//spin x axis , base on direction
	/*	double xspin[] = {
		1,0,0,0,
		0,cos(theta),-sin(theta),0,
		0,sin(theta),cos(theta),0,
		0,0,0,1
		};
	 */

	double xspin[] = {
		1,0,0,0,
		0,direction.z/sqrt(pow(direction.z,2)+ pow(direction.y, 2)),-direction.y/sqrt(pow(direction.z,2)+ pow(direction.y, 2)),0,
		0,direction.y/sqrt(pow(direction.z,2)+ pow(direction.y, 2)),direction.z/sqrt(pow(direction.z,2)+ pow(direction.y, 2)),0,
		0,0,0,1
	};
	Matrix xspinMatrix(4,4,xspin);

	//spin y axis , base on direction
	/*double yspin[] = {
	  cos(theta),0,sin(theta),0,
	  0,1,0,0,
	  -sin(theta),0,cos(theta),0,
	  0,0,0,1
	  };*/

	double yspin[] = {
		direction.z/sqrt(pow(direction.z,2)+ pow(direction.x, 2)),0,direction.x/sqrt(pow(direction.z,2)+ pow(direction.x, 2)),0,
		0,1,0,0,
		-direction.x/sqrt(pow(direction.z,2)+ pow(direction.x, 2)),0,direction.z/sqrt(pow(direction.z,2)+ pow(direction.x, 2)),0,
		0,0,0,1
	};
	Matrix yspinMatrix(4,4,yspin);

	//spin z axis , base on direction , dont use it here
	/*double zspin[] = {
	  cos(theta),sin(theta),0,0,
	  sin(theta),cos(theta),0,0,
	  0,0,1,0,
	  0,0,0,1
	  };*/

	double zspin[] = {
		direction.x/sqrt(pow(direction.x,2)+ pow(direction.y, 2)),-direction.y/sqrt(pow(direction.x,2)+ pow(direction.y, 2)),0,0,
		direction.y/sqrt(pow(direction.x,2)+ pow(direction.y, 2)),direction.x/sqrt(pow(direction.x,2)+ pow(direction.y, 2)),0,0,
		0,0,1,0,
		0,0,0,1
	};

	Matrix zspinMatrix(4,4,zspin);

	posiVector= transMatrix*posiVector;
	posiVector= xspinMatrix*posiVector;
	posiVector= yspinMatrix*posiVector;
	return Point3d(posiVector.dataAt(0,0), posiVector.dataAt(0,1), posiVector.dataAt(0,2));

}

Line2d Viewpoint::lookAtLine3D(const Line3d& l3d){
	return Line2d(lookAtPoint3D(l3d.p1), lookAtPoint3D(l3d.p2));
}

void Viewpoint::draw()const{

}

void Viewpoint::update(){
	//todo
}
