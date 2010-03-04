#include "world.hpp"
#include <cassert>

world::world()
: lights_(), master_(), camera_fov_(), bg_()
{
}

bool
world::init(double c, shape_composite sc, std::vector<light> l, rgb b)
{
  assert(c > 0);
  camera_fov_ = c;
  master_ = sc;
  lights_ = l;
  bg_ = b;
  return (true);
}


bool world::render()
{
  
}