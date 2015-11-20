#ifndef HUD_H
#define HUD_H
#include"obj3ddrawable.h"

class HUDObj3DDrawable: public Obj3DDrawable{

	public:
		HUDObj3DDrawable(const std::string& n, const Point3d& pos, const Point3d& vel, int lt):
			Obj3DDrawable(n, pos, vel),
			lifeTime(lt),
			seconds(0),
			fps(0){

				getProjectedLines().clear();
				getProjectedLines().push_back(Line2d(
							Point2d(410, 230),
							Point2d(200, 230)
							));

				
				std::cout << getScreen()->w << std::endl;

				getProjectedLines().push_back(Line2d(
							Point2d(200, 230),
							Point2d(200, 0)
							));

				getProjectedLines().push_back(Line2d(
							Point2d(200, 0),
							Point2d(410, 0)
							));

				getProjectedLines().push_back(Line2d(
							Point2d(410,0),
							Point2d(410,230)
							));

			}

		void setSecond(int s){seconds= s;}
		void setFPS(int f){fps = f;}

		void renewLifeTime(){
			lifeTime = 3000;
		}
		void update(Uint32 ticks);
		void draw()const ;

	private:
		int lifeTime;
		int seconds;
		int fps;

};

#endif
