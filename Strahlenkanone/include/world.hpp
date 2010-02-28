/* 
 * File:   world.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:33
 */

#ifndef _WORLD_HPP
#define	_WORLD_HPP

#include <light.hpp>
#include <rgb.hpp>
#include <shape_composite.hpp>
#include <vector>

using namespace std;

class world
{
public:
  //initialisierung für loader
  bool init(double c, shape_composite sc, vector<light> l, rgb b);
  //Bildberechnung. Vorläufig später Auslagerung in raytracer.hpp/cpp
  bool render();

private:
  //Vector mit allen Lichtern
  vector<light> lights_;
  //Composite mit allen Objekten
  shape_composite master_;
  //Kameraöffnungswinkel
  double camera_fov_;
  //Hintergrundfarbe:
  rgb bg_;
};

#endif	/* _WORLD_HPP */

