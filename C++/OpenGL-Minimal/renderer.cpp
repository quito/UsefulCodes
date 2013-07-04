
#include <SDL/SDL.h>
#include "renderer.hpp"

Renderer::Renderer(unsigned width, unsigned height,
		   std::string const &title) :
  _isRunning(true)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption(title.c_str(), NULL);
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective(70,(double)640/480,1,1000);
  glClear( GL_COLOR_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity(); 
  gluLookAt(3,4,2,0,0,0,0,0,1);
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

  this->manageEvent();
  for (; it != end; ++it)
    if (*it)
      (*it)->update();
  glFlush();
  SDL_GL_SwapBuffers();
  return _isRunning;
}

void		Renderer::createSphere(t_3Dcoord const &coords, float radius,
				       union u_color color)
{
  Sphere	*s = new Sphere(coords, radius, color);

  _Objects.push_back(s);
}
