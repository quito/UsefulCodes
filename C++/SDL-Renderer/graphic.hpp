
#ifndef GRAPHIC_HPP_
# define GRAPHIC_HPP_

# include <SDL/SDL.h>
# include <string>
# include <math.h>

typedef union
{
  unsigned	color;
  unsigned char	tab[4];
}		u_color;

class Graphic
{
protected:
  unsigned	_x;
  unsigned	_y;
  SDL_Surface	*_screen;

public:

  Graphic(unsigned x, unsigned y, std::string const &title = "");
  ~Graphic();
  void update(void);
  void PutPixel(int x, int y, Uint32 px);
  void SafePutPixel(int x, int y, Uint32 px);
  void	drawSquare(int x, int y, unsigned color, unsigned size);
  void drawLine(int x1,int y1, int x2,int y2, unsigned color);
  void drawCircle(int n_cx, int n_cy, int radius, Uint32 pixel);
  void fillCircle(int cx, int cy, int radius, Uint32 pixel);

};

// extern Graphic g;

#endif
