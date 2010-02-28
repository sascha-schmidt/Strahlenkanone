/* 
 * File:   shade.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:48
 */

#ifndef _SHADE_HPP
#define	_SHADE_HPP

#include <world.hpp>
#include <material.hpp>
#include <vector3d.hpp>

//Struktur zum Speichern der beim intersect gewonnen Informationen
struct shade
{
public:
  bool didhit; //Haben wir überhaupt getroffen
  //Pointer aufs Material:
  material* material_ptr;
  //Referenz zur Welt, ermöglicht Zugriff auf ihre Member
  world& world_ref;
  point3d hitpoint;
  //Normalvektor auf Schnittpunkt:
  vector3d n;
  //Abstand des Punktes zur Kamera um den sichtbaren Schnittpunkt zu ermitteln
  double distance;
};

#endif	/* _SHADE_HPP */

