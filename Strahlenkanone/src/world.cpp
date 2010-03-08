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
#include "phong.hpp"

#include <iostream>

world::world()
: master_(), camera_fov_(), bg_(), width_(500), heigth_(500), beleucht_()
{
}

bool
world::init(double const c, shape_composite const sc, std::vector<light> const l, rgb const a, rgb const b)
{
  assert(c > 0);
  camera_fov_ = c;
  master_ = sc;
  //phong(sc, l, b, a);
  bg_ = b;
  return (true);
}

unsigned
world::getwidth()
{
  return width_;
}

unsigned
world::getheigth()
{
  return heigth_;
}

rgb
world::getambient()
{
  //return ambient_;
}

rgb
world::getbg()
{
  return bg_;
}

bool world::render()
{
  glutwindow& gw=glutwindow::instance();
  ppmwriter pw(gw.width(), gw.height(), "./checkerboard.ppm");

  ray r;
  r.dir = vector3d(0.0, 0.0, -1.0);

  phong ph;

  for (std::size_t y=0; y < heigth_; ++y)
  {
    for (std::size_t x=0; x < width_; ++x)
    {
      pixel p(x, y);
      //Berechnung der Kamerafläche
      double ux = ( y - (0.5 * (heigth_ - 1)));
      double uy = ( x - (0.5 * (width_ - 1)));
      r.ori = point3d(ux, uy, 0.0);
      shade sh;
      sh.world_ptr = this;
      if(master_.intersect(r, sh))
      {
        //std::cout << "intersect bei" << x << ":" << y << std::endl;
        p.color = ph.color(sh);
      }
      else
      {
        p.color = bg_;
      }
      //ausgeben und schreiben
      gw.write(p);
      pw.write(p);
    }
  }
  //Bild speichern
  pw.save();
  return true;
}