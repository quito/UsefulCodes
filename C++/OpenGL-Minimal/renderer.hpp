
#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <SDL/SDL.h>
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
# include <cstdlib>
# include <string>
# include <list>
# include <iostream>

class MultiCube;

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

protected :
  std::list<IDisplayable*>	_childs;

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
    glTranslated(-_pos.x, -_pos.y, -_pos.z);
  }
  
};


class Text : public IDisplayable
{
public :

  static void drawBitmapText(char *string,float x,float y,float z) 
  {  
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) 
      {
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
      }
  }

  virtual void update()
  {
  }
};


class Cube : public IDisplayable
{
public :

  enum eType
    {
      WIRED = 1,
      SOLID = 2
    };

private :

  t_3Dcoord	_pos;
  float		_size;
  union u_color	_color;
  union u_color	_wireColor;
  enum eType	_type;
  

public :

  Cube(t_3Dcoord pos, float size, union u_color color,  enum eType type = SOLID) :
    _pos(pos),
    _size(size),
    _color(color),
    _type(type)
  {
  }

  virtual ~Cube()
  {
    // gluDeleteQuadric(_quadric);
  }



  void	drawBorderCube()
  {
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glMatrixMode( GL_MODELVIEW);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glEnd();
  }

  void	drawFilledCube()
  {
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glAlphaFunc(GL_GREATER, 0.2f);
    // glMatrixMode( GL_MODELVIEW );
    glBegin(GL_QUADS);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,-1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,-1 * _size / 2.f);
    glColor4ub(_color.c[0], _color.c[1], _color.c[2], _color.c[3]);
    glVertex3d(1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,1 * _size / 2.f,1 * _size / 2.f);
    glVertex3d(-1 * _size / 2.f,-1 * _size / 2.f,1 * _size / 2.f);
    glEnd();
  }
  
  virtual void update(void)
  {
    glPushMatrix();
    glTranslatef(_pos.x, _pos.y, _pos.z);
    if (_type & SOLID)
      drawFilledCube();
    if (_type & WIRED)
      drawBorderCube();
    glTranslatef(-_pos.x, -_pos.y, -_pos.z);
    glPopMatrix();
  }
};

class Renderer
{
  
private:

  SDL_Event			_event;
  bool				_isRunning;
  std::list<IDisplayable *>	_Objects;
  bool				_sortObject;

public:

  Renderer(int argc, char **argv,
	   unsigned width = 640, unsigned height = 480,
	   std::string const &title = "");
  ~Renderer();

  bool	update(void);
  void	manageEvent(void);

  void	createSphere(t_3Dcoord const &coords, float radius,
		     union u_color color);
  void	createCube(t_3Dcoord const &coords, float size,
		   union u_color color, enum Cube::eType type);
  void	createMultiCube(t_3Dcoord const &coords, float size, unsigned char ***data,
		   t_3Dcoord const &sizes, union u_color colorFilled,
		   union u_color colorEmpty);
  void	addMultiCube(MultiCube *l);
};

#endif
