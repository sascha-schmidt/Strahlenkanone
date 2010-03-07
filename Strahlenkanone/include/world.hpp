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

class world
{
public:
  world();
  //initialisierung für loader

  bool init(double const c, shape_composite const sc, std::vector<light> const l, rgb const la, rgb const b);

  //Bildberechnung. Vorläufig später Auslagerung in raytracer.hpp/cpp
  bool render();

  unsigned getwidth();
  unsigned getheigth();
  rgb getambient();
  rgb getbg();

private:
  //Vector mit allen Lichtern
  std::vector<light> lights_;
  //Composite mit allen Objekten
  shape_composite master_;
  //Kameraöffnungswinkel
  double camera_fov_;
  //Hintergrundfarbe:
  rgb bg_;
  rgb ambient_;
  unsigned width_; //Abmessung der Ausgabe
  unsigned heigth_;
};

#endif	/* _WORLD_HPP */

