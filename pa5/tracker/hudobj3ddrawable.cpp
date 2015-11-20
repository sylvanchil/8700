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
	
		IOManager::getInstance().printMessageAt("3d projection demo", 20,10);
		IOManager::getInstance().printMessageAt("w,a,s,d to move cube", 20,30);
		IOManager::getInstance().printMessageAt("hud will dispear in 3 sec", 20,50);
		//		std::cout << "hud displayed()" << std::endl;
		IOManager::getInstance().
		printMessageValueAt("Seconds: ", seconds, 20, 70);
	IOManager::getInstance().
		printMessageValueAt("fps: ", fps, 20, 90);
	
	}
}






