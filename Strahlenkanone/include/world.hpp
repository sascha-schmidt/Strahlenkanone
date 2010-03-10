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
#include <phong.hpp>

class world
{
public:
  world();
  //initialisierung für loader

  bool init(double c, shape_composite sc, std::vector<light> l, rgb la, rgb b);

  //Bildberechnung. Vorläufig später Auslagerung in raytracer.hpp/cpp
  bool render();

  unsigned getwidth();
  unsigned getheigth();

   
private:
  //Composite mit allen Objekten
  shape_composite master_;
  //Kameraöffnungswinkel
  double camera_fov_;
  //Hintergrundfarbe:
  rgb bg_;
  unsigned width_; //Abmessung der Ausgabe
  unsigned heigth_;
  phong beleucht_;
};

#endif	/* _WORLD_HPP */

