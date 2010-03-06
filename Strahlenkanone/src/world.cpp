#include "world.hpp"
#include <cassert>

#include <iostream>

world::world()
: lights_(), master_(), camera_fov_(), bg_()
{
}

bool
world::init(double const c, shape_composite const sc, std::vector<light> const l, rgb const la, rgb const b)
{
  assert(c > 0);
  camera_fov_ = c;
  master_ = sc;
  lights_ = l;
  bg_ = b;
  std::cout << "world initialisiert" << std::endl;
  return (true);
}


bool world::render()
{
  
}