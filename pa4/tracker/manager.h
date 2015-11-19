#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "3ddrawable.h"
#include "clock.h"

#include "background.h"

class Manager {
	public:
		Manager ();
		~Manager ();
		void play();
	private:
		const bool env;
		const IOManager& io;
		Clock& clock;

		SDL_Surface * const screen;
	//	World world;
	//	Viewport& viewport;

		Background background;
		std::list<Drawable3D*> objs;

		bool makeVideo;
		int frameCount;
		const std::string username;
		const std::string title;
		const int frameMax;

		bool updated;
		void draw() const;
		void update();

		Manager(const Manager&);
		Manager& operator=(const Manager&);
		void makeFrame();
};
