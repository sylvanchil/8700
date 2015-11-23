#ifndef _BLOCK_DRAWABLE_H_
#define _BLOCK_DRAWABLE_H_

#include"obj3ddrawable.h"

class Block3DDrawable: public Obj3DDrawable{

	public:
		Block3DDrawable(const std::string& n, const Point3d& p, const Point3d& vel,const Point3d& di,			double ts, double acc
				);
		/*	void turnRight(){turningRight= true;}
			void turnLeft(){turningLeft = true;}
			void accelerate(){accelerating= true;}
		 */
		void moveNorth(){
			VX(0);
			VY(0);
			VZ(200);
	//		accelerating = true;
		}
		void moveSouth(){
			VX(0);
			VY(0);
			VZ(-200);
	//		accelerating = true;
		}
		void moveEast(){
			VX(200);
			VY(0);
			VZ(0);
	//		accelerating = true;

		}
		void moveWest(){
			VX(-200);
			VY(0);
			VZ(0);
//
		}
		virtual void update(Uint32 ticks);

		void updateLinesPosition();

	private:
		Point3d dimension;	
		Point3d direction;
		double topSpeed;
		//	double topBackSpeed;
		double acceleration;

		bool accelerating;
		/*bool turningRight;
		  bool turningLeft;
		  bool accelerating;
		 */
};

#endif
