#include"ground3ddrawable.h"
#include"viewpoint.h"
#include"aaline.h"

Ground3DDrawable::Ground3DDrawable(const std::string& n, Point3d posi, Point3d vel, int w, int l, int lD):
	Obj3DDrawable(n, posi, vel),
	width(w),
	length(l),
	lineDistance(lD)
{

	
	for(int x = X()-length/2; x <=X()+length/2; x +=lineDistance){
		getLines().push_back(Line3d(Point3d(x, 0, Z() -width/2), Point3d(x, 0, Z()+ width/2)));
	}

	for(int z = Z() - width/2; z <= Z() + width/2; z += lineDistance){
		getLines().push_back(Line3d(Point3d(X()-length/2,0,z), Point3d(X() +length/2, 0, z)));
	}

	for(std::vector<Line3d>::iterator i = getLines().begin();i != getLines().end();i ++){
		getProjectedLines(). push_back(Viewpoint::getInstance().lookAtLine3D(*i));
	}


}
