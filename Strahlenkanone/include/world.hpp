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
<<<<<<< HEAD
  bool init(double const c, shape_composite const sc, std::vector<light> const l, rgb const la, rgb const b);
=======
  bool init(double c, shape_composite sc, std::vector<light> l, rgb b, rgb a);
>>>>>>> ce5bffe66348703ae86a7d18d2ff8fbc3091ab3a
  //Bildberechnung. Vorläufig später Auslagerung in raytracer.hpp/cpp
  bool render();

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
  unsigned x_; //Abmessung der Ausgabe
  unsigned y_;
};

#endif	/* _WORLD_HPP */

