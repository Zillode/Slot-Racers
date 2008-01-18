#ifndef __CSPRITEBASE_H__
#define __CSPRITEBASE_H__

#include <SDL/SDL.h>

struct CSpriteFrame
{
  CSpriteFrame() { }
  SDL_Surface *image;
  int pause;
};

class CSpriteBase
{
  public:
  CSpriteBase();
  ~CSpriteBase();
  int init(char *dir);

  CSpriteFrame *mAnim;
  int mBuilt, mNumframes, mW, mH;
  void softStrech(int nW, int nH);

};

#endif

