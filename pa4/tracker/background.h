#include<SDL.h>
#include"ioManager.h"

class Background{
public:
	Background():
		screen(IOManager::getInstance().getScreen()){
		
		}
	void draw()const ;
private:
	SDL_Surface * screen;
};
