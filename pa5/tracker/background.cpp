#include"background.h"
void Background::draw()const {
	SDL_FillRect( screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255) );
	SDL_Rect dest = {0, 0, 0, 0};
	SDL_BlitSurface( screen, NULL, screen, &dest );

}
