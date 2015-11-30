#include <list>
#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "3ddrawable.h"
#include "clock.h"

#include "background.h"
#include "ground3ddrawable.h"

#include "blockobj3ddrawable.h"
#include "hudobj3ddrawable.h"

#include "paperplaneobj3ddrawable.h"
#include "bulletpool.h"

#include "objexplode.h"

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
		Block3DDrawable* block;
		Ground3DDrawable* ground;
		HUDObj3DDrawable* hud;

		Plane3DDrawable* plane;

		BulletPool bp;

		Background background;
		std::list<Drawable3D*> objs;

		bool makeVideo;
		int frameCount;
		const std::string username;
		const std::string title;
		const int frameMax;
		
		bool godMode;
		
		bool updated;
		void draw() const;
		void update();

		void reset();

		void collisionDetect();

		Manager(const Manager&);
		Manager& operator=(const Manager&);
		void makeFrame();
};
