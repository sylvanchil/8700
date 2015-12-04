#include"hudobj3ddrawable.h"
#include"ioManager.h"
#include"aaline.h"
void HUDObj3DDrawable::update(Uint32 ticks){
	if(lifeTime >0){
		lifeTime-= ticks;
	}
	else{
		lifeTime = 0;
	}
}

void HUDObj3DDrawable::draw()const{	
	if(lifeTime> 0){
		Obj3DDrawable::draw();
		IOManager::getInstance().printMessageAt("w,a,s,d to move plane", 20,30);
		IOManager::getInstance().printMessageAt("space to shoot", 20,50);
		IOManager::getInstance().printMessageAt("g to godmode", 20,70);
		IOManager::getInstance().printMessageAt("r to reset", 20,90);
		IOManager::getInstance().printMessageAt("i to auto aim ", 20,110);
		//		std::cout << "hud displayed()" << std::endl;
		IOManager::getInstance().
		printMessageValueAt("Seconds: ", seconds, 20, 130);
		IOManager::getInstance().
		printMessageValueAt("fps: ", fps, 20, 150);
	IOManager::getInstance().
		printMessageValueAt("bulletpool: ", bullet, 20, 170);
		IOManager::getInstance().
		printMessageValueAt("freeList: ", freebullet, 20, 190);
	
	}
}






