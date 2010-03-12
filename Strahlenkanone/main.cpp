#include <glutwindow.hpp>
#include <ppmwriter.hpp>
#include <pixel.hpp>

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include "world.hpp"
#include "loader.hpp"
#include <shape.hpp>
#include "sphere.hpp"
#include "cuboid.hpp"
#include "triangle.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// this is a dummy raytrace application

class rt_application
{
public:

  void raytrace() const
  {
    // size of a tile in checkerboard
    const std::size_t checkersize=20;

    // get glutwindow instance
    glutwindow& gw=glutwindow::instance();

    // create a ppmwriter
    ppmwriter pw(gw.width(), gw.height(), "./checkerboard.ppm");

    // for all pixels of window
    for (std::size_t y=0; y < gw.height(); ++y)
    {
      for (std::size_t x=0; x < gw.width(); ++x)
      {

        // create pixel at x,y
        pixel p(x, y);

        // compute color for pixel
        if (((x / checkersize) % 2) != ((y / checkersize) % 2))
        {
          p.color=rgb(1.0, 1.0, float(x) / gw.height());
        } else
        {
          p.color=rgb(1.0, 0.0, float(y) / gw.width());
        }

        // write pixel to output window
        gw.write(p);

        // write pixel to image writer
        pw.write(p);
      }
    }

    // save final image
    pw.save();
  }

private: // attributes

  // you may add a scene description here

};

int main(int argc, char* argv[])
{
  // create a ray tracing application
  //rt_application app;


  // load sdf file
  loader l;
  world one;
  
  bool result=l.load(argv[1], one);
  if (!result) std::exit(1);

/*
  material red   (rgb (1,0,0), rgb (1,0,0), rgb (1,0,0), 1);
  material white (rgb (1,1,1), rgb (1,1,1), rgb (1,1,1), 1);
  material blue  (rgb (0,0,1), rgb (0,0,1), rgb (0,0,0.5), 2);
  material stuff (rgb (0.5,0.5,0.5), rgb (0.5,0.5,0.5), rgb (0.5,0.5,0.5), 2);

  shape*  c = new cuboid(point3d(220.0, 100.0, -180.0), point3d(-210.0, 10.0, -181.0), blue);
  shape*  s = new sphere(point3d(20.0, 40.0, -190), 90, stuff);
  shape*  s1 = new sphere(point3d(20.0, 120.0, -190), 40, stuff);
  shape*  s2 = new sphere(point3d(20.0, -72.0, -190), 40, stuff);
  shape*  s3 = new sphere(point3d(20.0, 40.0, -100), 60, stuff);
  shape*  t = new triangle(point3d(-60.0, -240.0, -340.0)
          , point3d(100.0, -240.0, -40.0), point3d(140.0, 240.0, -4.0), white);
  
  shape_composite sc;
  sc.add(t);
  sc.add(s);
  sc.add(c);
  sc.add(s1);
  sc.add(s2);
  sc.add(s3);

  light li  (point3d(0.0, 200.0, 50.0), rgb(0.6,0.6,0.6));
  light li2 (point3d(100.0,-200.0, 10.0), rgb(0.4,0.4,0.4));
  light li3 (point3d(-100.0,-200.0, 10.0), rgb(0.9,0.9,0.9));
  std::vector<light> vl;
  vl.push_back(li);
  vl.push_back(li2);
  vl.push_back(li3);
*/
  // create output window
  glutwindow::init(one.getwidth(), one.getheigth(), 500, 500, "CheckerBoard", argc, argv);


  // start computation in thread
  //boost::thread thr(boost::bind(&rt_application::raytrace, &app));
//  one.init(1.0, sc, vl, rgb(0.1,0.1,0.1), rgb(0,0,0));
  one.render();
  // start output on glutwindow
  glutwindow::instance().run();

  // wait on thread
  //thr.join();

  return 0;
}