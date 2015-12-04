#include"explosionpool.h"

void ExplosionPool::explode(const Point3d& pos, const Point3d& vel){
	if(freeList.empty()){
		explosionList.push_back(new Explosion("explostion", pos, vel));
	}else
	{
		Explosion* e = freeList.front();
		freeList.pop_front();
		e->set(pos, vel, 7000);
		explosionList.push_back(e);
	}
}

void ExplosionPool::draw()const{
	std::list<Explosion*>::const_iterator i = explosionList.begin();
	while(i != explosionList.end()){
	(*i)->draw();
i++;
	}
}

void ExplosionPool::update(Uint32 ticks){
	std::list<Explosion*>::iterator i = explosionList.begin();

	while(i!= explosionList.end()){
		(*i)-> update(ticks);
		if(!(*i)->alive()){
			freeList.push_back(*i);
			i = explosionList.erase(i);
		}
		else{
			i ++;
		}

	}

}
