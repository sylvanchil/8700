#ifndef RCMULTISPRITE_H
#define RCMULTISPRITE_H
#include<string>
#include<vector>
#include<cmath>
#include"multisprite.h"

class RandomCloudMultiSprite: public MultiSprite{
public:
	RandomCloudMultiSprite(const std::string name):
		MultiSprite(name)
	{	
		X(rand()%2000);
		Y(Y()+rand()%20 - rand()%10);
		
	}
};

#endif
