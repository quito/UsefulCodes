#include "renderer.hpp"

 
int main(int argc, char *argv[])
{
  Renderer r;
  t_3Dcoord pos = {0, 0, 0};
  union u_color color;
  color.c[0] = 0;
  color.c[1] = 0xFF;
  color.c[2] = 255;
  color.c[4] = 0;

  r.createSphere(pos, 0.5, color);
  while (r.update());
  return 0;
}
