#ifndef BULLETPOOL_H
#define BULLETPOOL_H
#include "bullet.h"
#include <list>
#include "geo.h"

class BulletPool
{
	public:
		BulletPool():
			bulletList(),
			freeList(){}
		~BulletPool(){};
		
		void shoot(const Point3d& pos, const Point3d& vel);
		void draw()const;
		void update(Uint32 ticks);
		
		std::list<Bullet*>& getBulletList(){ return bulletList;}
		
		int bulletSize(){return bulletList.size();}
		int freeSize(){return freeList.size();}
	private:
		std::list<Bullet*> bulletList;
		std::list<Bullet*> freeList;

		BulletPool(const BulletPool& bm);
};


#endif

