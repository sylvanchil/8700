#ifndef SPRITE__H
#define SPRITE__H

#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  // In this version, frame is a parameter:
  Sprite(const std::string&, const Frame* const);  
  Sprite(const Sprite& s); // canonical form
  virtual ~Sprite() { }  // Don't delete frame; manager will reuse it 
  Sprite& operator=(const Sprite&); // canonical form

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual void posiUpdate(Uint32 ticks);
  virtual const Frame* getFrame() const { return frame; }
	

  virtual void shiftPosi(float x, float y);

  virtual void speedUpdate(Uint32 ticks);
  //randomize speed
  virtual void randomSpeed();
  //SpeedDown due to fraction
  virtual void fractionSpeedDown();
  //gravity
  virtual void gravity(Uint32 ticks);
virtual void gotoPosi(int x, int y);

private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int accValue;
	int getDistance(const Sprite*) const;
};
#endif
