/* 
 * File:   shade.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:48
 */

#ifndef _SHADE_HPP
#define	_SHADE_HPP

//#include "world.hpp"
#include <material.hpp>
#include <vector3d.hpp>
#include "point3d.hpp"
#include <limits>

class world;

//Struktur zum Speichern der beim intersect gewonnen Informationen
struct shade
{
public:
  bool didhit; //Haben wir überhaupt getroffen
  //Pointer aufs Material:
  material nothing;
  material& material_ref;
  point3d hitpoint;
  //Normalvektor auf Schnittpunkt:
  vector3d n;
  //Abstand des Punktes zur Kamera um den sichtbaren Schnittpunkt zu ermitteln
  double distance;

  shade()
  :didhit(false), material_ref(nothing), hitpoint(), n(), distance(std::numeric_limits<double>::max())
  {}

};

#endif	/* _SHADE_HPP */

