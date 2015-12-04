#ifndef EXPLOSIONPOOL_H
#define EXPLOSIONPOOL_H

#include "explosion.h"
#include<list>
#include"geo.h"

class ExplosionPool{
public:
	ExplosionPool():
		explosionList(),
		freeList(){}
	~ExplosionPool(){};

	void explode(const Point3d& pos, const Point3d& vel);
	void draw()const;
	void update(Uint32 ticks);

	std::list<Explosion*>& getExplisionList(){return explosionList;}
	int explosionCount(){return explosionList.size();}
	int freeSize(){return freeList.size();}
private:
	std::list<Explosion*> explosionList;
	std::list<Explosion*> freeList;

	ExplosionPool(const ExplosionPool& ep);

};

#endif
