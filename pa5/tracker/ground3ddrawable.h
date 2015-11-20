#include"obj3ddrawable.h"
#include"viewpoint.h"

class Ground3DDrawable: public Obj3DDrawable{
	public:

		Ground3DDrawable(const std::string& n, Point3d posi, Point3d vel, int w, int l, int lD);
	private:	
		int width;
		int length;
		int lineDistance;
};
