/*
  font.h
  Header for the Cone3D SDL font routines.
  Made by Marius Andra 2002
  http://cone3d.gamedev.net

  You can use the code for anything you like.
  Even in a commercial project.
  But please let me know where it ends up.
  I'm just curious. That's all.
*/

#include <SDL/SDL.h>    // just in case...
#include <string>

// Structure to hold our font
struct SDLFont
{
  SDL_Surface *font;    // The SDL Surface for the font image
  int width;            // Width of the SDL Surface (same as the height)
  int charWidth;        // Width of one block character in the font (fontWidth/16)
  int *widths;          // Real widths of all the fonts
  unsigned char *data;  // The raw font data
};

// Function prototypes

// This function initalizes a font
SDLFont *initFont(std::string fontdir, float r, float g, float b, float a);

// Some overloaded functions to make your life easier
inline SDLFont *initFont(std::string fontdir, float r, float g, float b) { return initFont(fontdir, r,g,b,1); }
inline SDLFont *initFont(std::string fontdir) { return initFont(fontdir, 1,1,1,1); }

// This function draws a string
void drawString(SDL_Surface *screen, SDLFont *font, int x, int y, const char *str,...);

// This function returns the width of a string
int stringWidth(SDLFont *font, std::string str,...);

// This function destroys the font
void freeFont(SDLFont *font);

