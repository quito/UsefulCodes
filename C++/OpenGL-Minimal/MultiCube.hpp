
#ifndef MULTICUBE_HPP_
# define MULTICUBE_HPP_

# include <vector>
# include <cstdlib>
# include "renderer.hpp"

typedef std::vector<char> vectorChar;

class MultiCube : public IDisplayable
{
private:

  t_3Dcoord	_coords;
  
  unsigned char	***_multiCube;
  float		_Ratio;
  union u_color _colorFilled;
  union u_color _colorEmpty;

  unsigned	_sizeX;
  unsigned	_sizeY;
  unsigned	_sizeZ;

  t_3Dcoord	_rotationVector;
  float		_angle;

public:

  MultiCube(t_3Dcoord const &coords, float size, unsigned char ***data,
	    t_3Dcoord const &sizes, union u_color colorFilled,
	    union u_color colorEmpty) :
    _multiCube(NULL),
    _Ratio(size),
    _colorFilled(colorFilled),
    _colorEmpty(colorEmpty),
    _angle(0)
    
  {
    _coords.x = coords.x;
    _coords.y = coords.y;
    _coords.z = coords.z;

    _rotationVector.x = 0;
    _rotationVector.y = 0;
    _rotationVector.z = 0;

    loadMultiCube(data, sizes.x, sizes.y, sizes.z);
    drawMultiCube();
  }

  void		addRot(float angle, t_3Dcoord vect)
  {
    _angle += angle;
    _rotationVector.x = vect.x;
    _rotationVector.y = vect.y;
    _rotationVector.z = vect.z;
  }

  void		deleteChilds();
  void		loadMultiCube(unsigned char ***MultiCube, unsigned sizeX, unsigned sizeY, unsigned sizeZ);
  void		drawMultiCube();
  virtual void	update();



};

#endif
