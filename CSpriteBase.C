#include "CSpriteBase.h"
#include <string.h>
#include <SDL/SDL_rotozoom.h>

CSpriteBase::CSpriteBase()
{ }

CSpriteBase::~CSpriteBase()
{
	delete [] mAnim;
}


int CSpriteBase::init(char *dir)
{
  char buffer[255];
  char filename[255];
  char name[255];
  int pause=0, r=0, g=0, b=0;
  FILE *fp;

  sprintf(filename, "%s/info", dir);

  if((fp=fopen(filename, "r")) == NULL)
  {
    printf("ERROR opening file %s\n\n", filename);
    return -1;
  }

  fgets(buffer, 255, fp);
  sscanf(buffer, "FILES: %d", &mNumframes);
  mAnim = new CSpriteFrame[mNumframes];

  mBuilt = 1;
  int count = 0;

  while(!feof(fp) && count<mNumframes)
  {
    fgets(buffer, 255, fp);
    if(buffer[0] != '#' && buffer[0] != '\r' && buffer[0] != '\0' && buffer[0] != '\n' && strlen(buffer) != 0)
    {
      sscanf(buffer, "%s %d %d %d %d", name, &pause, &r, &g, &b);
      sprintf(filename, "%s/%s", dir, name);
      SDL_Surface *temp;
      if((temp = SDL_LoadBMP(filename)) == NULL) return -1;
      if(r >= 0) SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, r, g, b));
      mAnim[count].image = SDL_DisplayFormat(temp);
      SDL_FreeSurface(temp);

      mAnim[count].pause = pause;
      if(!mW) mW = mAnim[count].image->w; if(!mH) mH = mAnim[count].image->w;

      count++;
    }
  }
  fclose(fp);
  return 0;
}

void CSpriteBase::softStrech(int nW, int nH) {
	for (int i(0); i < mNumframes; ++i) {
		SDL_Surface *imgold = mAnim[i].image;
		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = mW;
		src.h = mH;
		SDL_Rect dest;
		dest.y = 0;
		dest.w = nW;
		dest.h = nH;
		double zoomx = mW/nW;
		double zoomy = mH/nH;
		mAnim[i].image = rotozoomSurfaceXY(mAnim[i].image, 0, zoomx, zoomy, 0);
		SDL_FreeSurface(imgold);
	}
	mW = nW;
	mH = nH;
}

