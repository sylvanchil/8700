#ifndef EXPLODE_H
#define EXPLODE_H

#include"sparkle.h"
#include"3ddrawable.h"
#include<vector>
class ObjExplosion: public Drawable3D{

	public:
		ObjExplosion(Drawable3D* d3d):
			Drawable3D(d3d->getName(), d3d->getPosition(), d3d->getVelocity()),
			sparkles()
	{
		for(int i =0;i != 100;i ++){
			double vx = VX() +rand()%1000/(double)1-50;
			double vy = VY()+ rand()%1000/(double)1-50;
			double vz = VZ()+ rand()%1000/(double)1-50;
			sparkles.push_back(
				
					Sparkle(getPosition(), Point3d(vx,vy,vz))
					);

		}

	}

		ObjExplosion(const Point3d&, const Point3d&);

		void draw() const {
			for(std::vector<Sparkle>::const_iterator i = sparkles.begin();i != sparkles.end(); i++){
				(*i).draw();
			}
		}
		void update(Uint32 ticks){
			for(std::vector<Sparkle>::iterator i = sparkles.begin();i != sparkles.end(); i++){
				(*i).update(ticks);
			}
		}


	private:
		std::vector<Sparkle> sparkles;

};

#endif 
