#include"bulletpool.h"


void BulletPool::shoot(const Point3d& pos, const Point3d& vel){
	Point3d bulletVel(vel.x*4 , vel.y* 4, vel.z *4);

	if(freeList.empty())
	{
		bulletList.push_back(new Bullet("bullet", pos, bulletVel));

	} 
	else
	{
		Bullet *b = freeList.front();
		freeList.pop_front();
		b->set(pos, bulletVel, 10000);
		bulletList.push_back(b); 
	}	
	std::cout << bulletList.size()<< std::endl;
}

void BulletPool::draw()const{
	std::list<Bullet*>::const_iterator ptr = bulletList.begin();
	while(ptr != bulletList.end())
	{
		(*ptr)->draw();
		ptr++;
	}
}

void BulletPool::update(Uint32 ticks){
	std::list<Bullet*>::iterator ptr = bulletList.begin();
	while(ptr != bulletList.end())
	{
		(*ptr)->update(ticks);
		if(!(*ptr)->alive())
		{
			freeList.push_back(*ptr);
			ptr = bulletList.erase(ptr);
		}
		else
			ptr++;
	}
}
