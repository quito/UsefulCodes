
#include "MultiCube.hpp"

void		MultiCube::loadMultiCube(unsigned char ***multiCube, unsigned sizeX, unsigned sizeY, unsigned sizeZ)
{
  unsigned i;
  unsigned j;
  unsigned k;
  
  if (_multiCube && *_multiCube)
    {
      delete *_multiCube;
      delete _multiCube;
    }
  
  _multiCube = new unsigned char **[sizeX];
  for (i = 0 ; i < sizeX ; ++i)
    {
      _multiCube[i] = new unsigned char *[sizeY];
      for (j = 0 ; j < sizeY ; ++j)
	{
	  _multiCube[i][j] = new unsigned char [sizeZ];
	  for (k = 0 ; k < sizeZ ; ++k)
	    _multiCube[i][j][k] = multiCube[i][j][k];
	}
    }
  _sizeX = sizeX;
  _sizeY = sizeY;
  _sizeZ = sizeZ;
}

void	MultiCube::deleteChilds()
{
  std::list<IDisplayable *>::iterator	it =  _childs.begin();
  std::list<IDisplayable *>::iterator	end = _childs.end();

  for (;it != end;++it)
    if (*it)
      delete *it;
  _childs.clear();
  drawMultiCube();
}

void	MultiCube::drawMultiCube()
{
  unsigned i;
  unsigned j;
  unsigned k;

  t_3Dcoord pos = {1, 1, 1};

  if (!_multiCube || !*_multiCube)
    return;
  for (i = 0 ; i < _sizeX ; ++i)
    {
      pos.x = ((float)_sizeX - (float)i) * _Ratio;
      for (j = 0 ; j < _sizeY ; ++j)
  	{
  	  pos.y = ((float)_sizeY - (float)j) * _Ratio;
  	  pos.y = (float)j * _Ratio;
  	  for (k = 0 ; k < _sizeZ ; ++k)
  	    {
  	      pos.z = ((float)_sizeZ - (float)k) * _Ratio;
  	      // std::cout << "posz: " << pos.z<< std::endl;
	      if ((i == 0 && j == 0 && k == 0) || _multiCube[i][j][k] > 1)
		{
		    union u_color color;
		    color.c[0] = 0xFF;
		    color.c[1] = 0x00;
		    color.c[2] = 0x00;
		    color.c[3] = 0xA0;
		    Cube *c = new Cube(pos, _Ratio, color, Cube::SOLID);
		  _childs.push_back(c);
		    color.c[0] = 0x9a;
		    color.c[1] = 0x9a;
		    color.c[2] = 0x9a;
		    color.c[3] = 255;
		    c = new Cube(pos, _Ratio, color, Cube::WIRED);
		  _childs.push_back(c);

		}
	      if ((i == 6 && j == 6 && k == 6))
		{
		    union u_color color;
		    color.c[0] = 0x00;
		    color.c[1] = 0xFF;
		    color.c[2] = 0x00;
		    color.c[3] = 0xA0;
		    Cube *c = new Cube(pos, _Ratio, color, Cube::SOLID);
		  _childs.push_back(c);
		    color.c[0] = 0x9a;
		    color.c[1] = 0x9a;
		    color.c[2] = 0x9a;
		    color.c[3] = 255;
		    c = new Cube(pos, _Ratio, color, Cube::WIRED);
		  _childs.push_back(c);

		}
  	      else if (_multiCube[i][j][k] == 0)
		{
		  Cube		*c = new Cube(pos, _Ratio, _colorFilled, Cube::SOLID);
		  _childs.push_back(c);
		 
		    union u_color color;
		    color.c[0] = 0x9a;
		    color.c[1] = 0x9a;
		    color.c[2] = 0x9a;
		    color.c[3] = 255;
		    c = new Cube(pos, _Ratio, color, Cube::WIRED);
		  _childs.push_back(c);

		  // c = new Cube(pos, _Ratio, color2, Cube::WIRED);

		  // _renderer.createCube(pos, _Ratio, color, Cube::SOLID);
		  // _renderer.createCube(pos, _Ratio, color2, Cube::WIRED);
		}
  	      else
		{
		  Cube	  *c = new Cube(pos, _Ratio, _colorEmpty, Cube::WIRED);
		  _childs.push_back(c);
		  // c = new Cube(pos, _Ratio, _colorEmpty, Cube::WIRED);
		  // _childs.push_back(c);
		}  		// _renderer.createCube(pos, _Ratio, color2, Cube::WIRED);
  	    }
  	}
    }
  
}


void		MultiCube::update()
{
  std::list<IDisplayable *>::iterator	it =  _childs.begin();
  std::list<IDisplayable *>::iterator	end = _childs.end();
  
  glTranslatef(_coords.x + (((float)_sizeX +1) * _Ratio) / 2.f, _coords.y + (((float)_sizeX - 1) * _Ratio) / 2.f,
  	       _coords.z + (((float)_sizeZ + 1) * _Ratio) / 2.f);
  glRotatef(_angle, _rotationVector.x, _rotationVector.y, _rotationVector.z);
  glTranslatef(-(_coords.x + (((float)_sizeX + 1) * _Ratio) / 2.f), -(_coords.y + (((float)_sizeX - 1) * _Ratio) / 2.f),
  	       -(_coords.z + (((float)_sizeZ + 1) * _Ratio) / 2.f));
  for (; it != end; ++it)
    if (*it)
      (*it)->update();
  _rotationVector.x = 5;
  _rotationVector.z = 10;

  _angle = 1;
}
