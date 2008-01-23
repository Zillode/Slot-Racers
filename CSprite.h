/*
  CSprite.h
  Header for the simple SDL sprite class.
  Made by Marius Andra 2001
  http://cone3d.gamedev.net

  You can use the code for anything you like.
  Even in a commercial project.
  But please let me know where it ends up.
  I'm just curious. That's all.
*/

#ifndef __CSPRITE_H__
#define __CSPRITE_H__

#include <SDL/SDL.h>

#include "CSpriteBase.h"

class CSprite
{
  public:
  CSprite(bool stopanim);
  ~CSprite();
  int init(CSpriteBase *base, SDL_Surface *screen);
  void draw(uint direction);
  void clearBG();
  void updateBG();

  void setFrame(int nr) { mFrame = nr; }
  int getFrame() { return mFrame; }

  void setSpeed(float nr) { mSpeed = nr; }
  float getSpeed() { return mSpeed; }

  void toggleAnim() { mAnimating = !mAnimating; }
  void startAnim() { mAnimating = 1; }
  void stopAnim() { mAnimating = 0; }
  void rewind() { mFrame = 0; }

  void xadd(uint nr) { mX+=nr; }
  void yadd(uint nr) { mY+=nr; }
  void xset(uint nr) { mX=nr; }
  void yset(uint nr) { mY=nr; }
  void set(uint xx, uint yy) { mX=xx; mY=yy; }

  float getx() {return mX;}
  float gety() {return mY;}

  int getw() {return mSpriteBase->mAnim[0].image->w;}
  int geth() {return mSpriteBase->mAnim[0].image->h;}

  private:
  int mFrame;
  uint mX, mY, mOldX, mOldY;
  float mSpeed;
  int mAnimating;
  int mDrawn;
  long mLastupdate;
  bool mStopAnim;
  CSpriteBase *mSpriteBase;
  SDL_Surface *mBackreplacement;
  SDL_Surface *mScreen;
};

#endif
