#include "world.hpp"
#include <cassert>
#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>
#include <GL/glut.h>
#include "rgb.hpp"
#include "ray.hpp"
#include "shade.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "cuboid.hpp"
#include "triangle.hpp"
#include <iostream>

#include <iostream>

world::world()
: lights_(), master_(), camera_fov_(), bg_(), x_(640), y_(480), ambient_()
{
}

bool
world::init(double const c, shape_composite const sc, std::vector<light> const l, rgb const a, rgb const b)
{
  assert(c > 0);
  camera_fov_ = c;
  master_ = sc;
  lights_ = l;
  bg_ = b;
  ambient_ = a;
  return (true);
}


bool world::render()
{
  ray r;
  r.dir = vector3d(0.0, 0.0, -1.0);
  glutwindow& gw=glutwindow::instance();
  for (std::size_t y=0; y < gw.height(); ++y)
  {
    for (std::size_t x=0; x < gw.width(); ++x)
    {
      pixel p(x, y);
      double ux = ( y - (0.5 * (gw.width() - 1)));
      double uy = ( x - (0.5 * (gw.height() - 1)));
      r.ori = point3d(ux, uy, 100.0);
      shade sh;
      if(master_.intersect(r, sh))
      {
        std::cout << "intersect bei" << x << ":" << y << std::endl;
        p.color = rgb(255,0,255);
      }
      else
      {
        p.color = bg_;
      }
      gw.write(p);
    }
  }
}