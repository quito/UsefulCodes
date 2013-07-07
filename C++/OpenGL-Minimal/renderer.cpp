
#include <SDL/SDL.h>
#include "renderer.hpp"
#include "MultiCube.hpp"

Renderer::Renderer(int argc, char **argv,
		   unsigned width, unsigned height,
		   std::string const &title) :
  _isRunning(true)
{
  glutInit(&argc, argv);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(title.c_str(), NULL);
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)800/600,1,1000);


  glEnable(GL_DEPTH_TEST);
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); 
  gluLookAt(3,5,2,0,0,0,0,0,1);
  glEnable(GL_LINE_SMOOTH);
}


Renderer::~Renderer()
{
  std::list<IDisplayable *>::iterator	it =  _Objects.begin();
  std::list<IDisplayable *>::iterator	end = _Objects.end();

  for (; it != end; ++it)
    delete *it;
  SDL_Quit();
}

void		Renderer::manageEvent(void)
{
  SDL_PollEvent(&_event);
  if (_event.type == SDL_QUIT)
    _isRunning = false;
  else if (_event.key.keysym.sym == SDLK_ESCAPE)
    _isRunning = false;
}

bool		Renderer::update()
{
  std::list<IDisplayable *>::iterator	it =  _Objects.begin();
  std::list<IDisplayable *>::iterator	end = _Objects.end();

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  this->manageEvent();
  for (; it != end; ++it)
    if (*it)
      (*it)->update();
  glFlush();
  SDL_GL_SwapBuffers();
  return _isRunning;
}

void		Renderer::createCube(t_3Dcoord const &coords, float size,
				     union u_color color, enum Cube::eType type)
{
  Cube		*c = new Cube(coords, size, color, type);
  _Objects.push_back(c);
}

void		Renderer::createMultiCube(t_3Dcoord const &coords, float size, unsigned char ***data,
				     t_3Dcoord const &sizes, union u_color colorFilled,
				     union u_color colorEmpty)
{
  MultiCube		*l = new MultiCube(coords, size, data, sizes, colorFilled, colorEmpty);
  _Objects.push_back(l);
}

void		Renderer::addMultiCube(MultiCube *l)
{
  _Objects.push_back(l);
}

void		Renderer::createSphere(t_3Dcoord const &coords, float radius,
				       union u_color color)
{
  Sphere	*s = new Sphere(coords, radius, color);
  _Objects.push_back(s);
}
