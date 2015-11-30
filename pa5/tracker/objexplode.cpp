#include"objexplode.h"
#include<string>


ObjExplosion::ObjExplosion(const Point3d& pos, const Point3d& vel):
	Drawable3D(std::string("explosion"), pos, vel),
	sparkles()
{
		for(int i =0;i != 100;i ++){
			double vx = VX() +rand()%1000/(double)1-50;
			double vy = VY()+ rand()%1000/(double)1-50;
			double vz = VZ()+ rand()%1000/(double)1-50;
			std::cout << pos.z << std::endl;

			sparkles.push_back(
				Sparkle(pos, Point3d(vx,vy,vz))
			);
			
		}
	
}
