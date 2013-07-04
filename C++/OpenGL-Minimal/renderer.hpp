
#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <SDL/SDL.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <cstdlib>
# include <string>
# include <list>
# include <iostream>

union u_color
{
  unsigned int	color;
  char		c[4];
};

typedef struct	s_3Dcoord
{
  float		x;
  float		y;
  float		z;
}		t_3Dcoord;

class IDisplayable
{

public:

  virtual void update(void) = 0;
};

class Sphere : public IDisplayable
{

private:

  t_3Dcoord	_pos;
  float		_radius;
  union u_color	_color;
  GLUquadric	*_quadric;

public:

  Sphere(t_3Dcoord const &pos, float radius, union u_color color) :
    _radius(radius),
    _color(color)
  {
    _pos.x = pos.x;
    _pos.y = pos.y;
    _pos.z = pos.z;
    _quadric = gluNewQuadric();
  }
  virtual ~Sphere()
  {
    gluDeleteQuadric(_quadric);
  }
  
  virtual void update(void)
  {
    glColor3ub(_color.c[0], _color.c[1], _color.c[2]);
    gluQuadricDrawStyle(_quadric,GLU_FILL);
    gluQuadricTexture(_quadric,GL_TRUE);
    glTranslated(_pos.x, _pos.y, _pos.z);
    gluSphere(_quadric, _radius, 200, 20);
  }
  
};

class Renderer
{
  
private:

  SDL_Event			_event;
  bool				_isRunning;
  std::list<IDisplayable *>	_Objects;

public:

  Renderer(unsigned width = 640, unsigned height = 480,
	   std::string const &title = "");
  ~Renderer();

  bool	update(void);
  void	manageEvent(void);

  void	createSphere(t_3Dcoord const &coords, float radius,
		     union u_color color);
};

#endif
