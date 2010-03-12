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

int main(int argc, char* argv[])
{


  // load sdf file
  loader l;
  world one;

  bool result=l.load(argv[1], one);
  if (!result) std::exit(1);

  // create output window
  glutwindow::init(one.getwidth(), one.getheigth(), 500, 500, "Strahlenkanone", argc, argv);

  one.render();
  // start output on glutwindow
  glutwindow::instance().run();

  return 0;
}