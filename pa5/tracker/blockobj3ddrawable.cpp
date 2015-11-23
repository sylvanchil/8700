#include"blockobj3ddrawable.h"
#include<cmath>

Block3DDrawable::Block3DDrawable(const std::string& n, const Point3d& p, const Point3d& vel,const Point3d& di,
		double ts,double acc
		):
	Obj3DDrawable(n, p, vel),
	dimension(di),
	direction(getVelocity()),
	topSpeed(ts),
//	topBackSpeed(tbs),
	acceleration(acc),
//	turningRight(false),
//	turningLeft(false),
	accelerating(false){

		//std::cout << X() << std::endl;
		//std::cout << Y() <<std::endl;
		//std::cout << Z() << std::endl;
		//std::cout << dimension.x << std::endl;
		//std::cout << dimension.y << std::endl;
		//std::cout << dimension.z << std::endl;

		getLines().clear();
		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
					Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()+ dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
					Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()+ dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
					Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()+ dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
					Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()+ dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() - dimension.z/2),
					Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() - dimension.z/2),
					Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() - dimension.z/2),
					Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
					));
		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() - dimension.z/2),
					Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
					));


		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
					Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
					));

		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
					Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
					));

		getLines().push_back(Line3d(
					Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
					Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
					));

		getLines().push_back(Line3d(
					Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
					Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
					));
		//add lines;
	}

void Block3DDrawable::update(Uint32 ticks){

//	turningRight = true;
	//	accelerating = true;	
//	double currentSpeed= sqrt(VX()*VX()+VY()*VY() + VZ()*VZ());	

	//	std::cout << currentSpeed << std::endl;
	//accelerating
/*	if(accelerating && currentSpeed < topSpeed){
		VX(VX()+VX()*acceleration*(VX()/currentSpeed)*ticks/1000);
		VY(VY()+VY()*acceleration*(VY()/currentSpeed)*ticks/1000);
		VZ(VZ()+VZ()*acceleration*(VZ()/currentSpeed)*ticks/1000);
	}
*/
	//not accelerating
/*	if(!accelerating && currentSpeed >0){
		if(VX()> VX()*acceleration*(VX()/currentSpeed)*ticks/1000){
			VX(VX()-VX()*acceleration*(VX()/currentSpeed)*ticks/1000);
		}else{
			VX(0);
		}
		if(VY()> VY()*acceleration*(VY()/currentSpeed)*ticks/1000){
			VY(VY()-VY()*acceleration*(VY()/currentSpeed)*ticks/1000);
		}else{
			VY(0);
		}
		if(VZ()> VZ()*acceleration*(VZ()/currentSpeed)*ticks/1000){
			VZ(VZ()-VZ()*acceleration*(VZ()/currentSpeed)*ticks/1000);
		}else{
			VZ(0);
		}
	}*/
/*
	//turning right
	if(turningRight){
	
//		std::cout << "turning" << std::endl;
		VZ(VZ()- VX()*0.1);
		VX(VX()+ VZ()*0.1);
	}

	if(turningLeft){
//		std::cout << "turning" << std::endl;
		VZ(VZ()+ VX()*0.1);
		VX(VX()- VZ()*0.1);


	}

	//turning left
*/
//	updateLinesPosition();

	Obj3DDrawable::update(ticks);

	//updateLinesPosition();
//	turningRight = false;
//	turningLeft = false;
	accelerating = false;
	VX(0);
	VY(0);
	VZ(0);
}

void Block3DDrawable::updateLinesPosition(){
	getLines().clear();
	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
				Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()+ dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
				Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()+ dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
				Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()+ dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
				Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()+ dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() - dimension.z/2),
				Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() - dimension.z/2),
				Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() - dimension.z/2),
				Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
				));
	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() - dimension.z/2),
				Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
				));


	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
				Point3d(X()+dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
				));

	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()+dimension.y/2,Z() + dimension.z/2),
				Point3d(X()-dimension.x/2,Y()+dimension.y/2, Z()- dimension.z/2)
				));

	getLines().push_back(Line3d(
				Point3d(X()-dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
				Point3d(X()-dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
				));

	getLines().push_back(Line3d(
				Point3d(X()+dimension.x/2,Y()-dimension.y/2,Z() + dimension.z/2),
				Point3d(X()+dimension.x/2,Y()-dimension.y/2, Z()- dimension.z/2)
				));


}

