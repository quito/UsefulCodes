#include "MultiCube.hpp"
#include "renderer.hpp"

char matris[7][49] = {
  { /* plan 0 */
    1, 1, 1, 0, 0, 1, 0,
    1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0,
    1, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 0,
  },
  { /* plan 1 */
    0, 0, 1, 0, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 1, 0, 0,
    1, 1, 1, 1, 0, 1, 0,
    1, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 1, 1, 1, 0,
  },
  { /* plan 2 */
    0, 0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1,
    1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1,
    1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 0, 0, 0,
  },
  { /* plan 3 */
    0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 1, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 0,
    1, 1, 1, 1, 0, 0, 0,
  },
  { /* plan 4 */
    0, 0, 1, 0, 0, 0, 0,
    0, 0, 1, 0, 1, 0, 0,
    1, 1, 1, 0, 1, 0, 1,
    0, 0, 1, 0, 0, 0, 1,
    0, 0, 1, 0, 0, 0, 1,
    0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0,
  },
  { /* plan 5 */
    0, 1, 0, 0, 0, 1, 1,
    0, 1, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 1, 0, 0,
    0, 1, 0, 1, 1, 1, 1,
    0, 0, 0, 0, 1, 0, 0,
    0, 1, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
  },
  { /* plan 6 */
    0, 1, 0, 0, 0, 0, 0,
    0, 1, 0, 1, 1, 0, 0,
    0, 1, 0, 0, 0, 0, 0,
    0, 1, 0, 1, 1, 1, 1,
    0, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 1, 1, 0, 1,
    0, 0, 0, 0, 0, 0, 1
  }
};
// char matris[7][49*2] = {
//   { /* plan 6 */
// };

unsigned char ***ConvertMultiCube(unsigned sizeX, unsigned sizeY, unsigned sizeZ)
{
  unsigned i;
  unsigned j;
  unsigned k;
  unsigned char ***_multiCuberinthe;

  _multiCuberinthe = new unsigned char **[sizeX];
  for (i = 0 ; i < sizeX ; ++i)
    {
      _multiCuberinthe[i] = new unsigned char *[sizeY];
      for (j = 0 ; j < sizeY ; ++j)
	{
	  _multiCuberinthe[i][j] = new unsigned char [sizeZ];
	  for (k = 0 ; k < sizeZ ; ++k)
	    {
	      // if (multiCube[i][j][k] == 0)
	      _multiCuberinthe[i][j][k] = matris[i][j * sizeZ + k];
	      // else
	      // 	_multiCuberinthe[i][j][k] = EMPTY;
	    }
	}
    }
  return _multiCuberinthe;
}
 
int main(int argc, char *argv[])
{
  Renderer r(argc, argv, 800, 600);
  // char (*tab)[7][7];
  // Renderer r(argc, argv, 1500, 900);
  t_3Dcoord pos = {0, 0, 0};
  union u_color color;
  color.c[0] = 0;
  color.c[1] = 0;
  color.c[2] = 255;
  color.c[3] = 100;

  // r.createSphere(pos, 0.5, color);
  // t_3Dcoord pos2 = {0, -1, 0};
  // r.createCube(pos2, 0.1, color, Cube::SOLID);
  // r.createCube(pos, 0.5, color, Cube::WIRED);
  // while (r.update());


  unsigned char ***multiCube = ConvertMultiCube(7, 7, 7);
  t_3Dcoord rot = {0, 0, 0};
  // t_3Dcoord pos = {0, 0, 0};
  float size = 0.3;
  t_3Dcoord sizeMultiCube = {7, 7, 7};
  union u_color colorFilled;
  colorFilled.c[0] = 0x10;
  colorFilled.c[1] = 0x00;
  colorFilled.c[2] = 0x5d;
  colorFilled.c[3] = 100;
  union u_color colorEmpty;
  colorEmpty.c[0] = 0x9a;
  colorEmpty.c[1] = 0x9a;
  colorEmpty.c[2] = 0x9a;
  colorEmpty.c[3] = 255;

  MultiCube *c =  new MultiCube(pos, size, multiCube, sizeMultiCube, colorFilled, colorEmpty);
  r.addMultiCube(c);
    do{
    } while (r.update());
  return 0;
}
