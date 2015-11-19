#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "sprite.h"
#include <vector>
class Manager {
	public:
		Manager ();
		~Manager ();
		void play();

	private:
		const bool env;
		IOManager& io;
		Clock& clock;

		SDL_Surface * const screen;

		SDL_Surface * backGroudSurface;
		const Frame * const  backGroundFrame; //(done)todo: delete this Frame in the destructor 
		Sprite backGround;

		SDL_Surface* orbSurface;
		const Frame * const orbFrame;
		std::vector<Sprite> orbs;
//		std::vector<Sprite> orbs2;
		std::vector<Sprite> orbsOriginalState;

		unsigned int rounds;

		bool makeVideo;
		int frameCount;
		std::string username;
		int frameMax;
		const std::string TITLE;
		

		void draw() ;
		void update();

		Manager(const Manager&);
		Manager& operator=(const Manager&);
};
