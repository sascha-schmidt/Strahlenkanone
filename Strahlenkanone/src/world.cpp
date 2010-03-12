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
#include <cmath>

world::world()
: master_(), camera_fov_(), bg_(), width_(500), heigth_(500), beleucht_(), filename_("image.ppm")
{
}

bool
world::init(double c, std::string filename, int width, int heigth, shape_composite sc, std::vector<light> l, rgb a, rgb b)
{
  assert(c > 0);
  camera_fov_ = c;
  master_ = sc;
  beleucht_.init(sc, l, a, b);
  bg_ = b;
  width_ = width;
  heigth_ = heigth;
  filename_ = filename;

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


bool world::render()
{
  glutwindow& gw=glutwindow::instance();
  ppmwriter pw(width_, heigth_, filename_);

  ray r;

  // Aus dem Öffnungswinkel der Abstand der Kamera berechnet
  // tan(90° - alpha/2) * breite/2

  double cam_abstand = std::tan(((90.0-camera_fov_)/2)*(M_PI/180))*width_*0.5;

  r.ori = point3d(0.0, 0.0, 0.0);

  std::cout << " camera abstand:" << cam_abstand << std::endl;
  std::cout << " breite:" << width_ << std::endl;


  r.ori = point3d(0.0, 0.0, 0.0);


  for (std::size_t y=0; y < heigth_; ++y)
  {
    for (std::size_t x=0; x < width_; ++x)
    {
      pixel p(x, y);
      //Berechnung der Kamerafläche
      double ux = ( y - (0.5 * (heigth_ - 1)));
      double uy = ( x - (0.5 * (width_ - 1)));

      r.dir = vector3d(r.ori, point3d(ux, uy, -cam_abstand));
      r.dir.normalize();

      
      shade sh;
      sh.world_ptr = this;
      master_.intersect(r, sh);
      if(sh.didhit)
      {
        p.color = beleucht_.color(r, sh);
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
  std::cout << "end" << std::endl;
  return true;
}