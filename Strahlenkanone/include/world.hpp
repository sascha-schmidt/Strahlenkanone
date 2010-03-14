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
#include <string>
#include <phong.hpp>

class world
{
public:
  world();
  //initialisierung für loader

  bool init(double c, std::string filename, int width, int heigth, shape_composite sc, std::vector<light> l, rgb la, rgb b);

  //Bildberechnung Auslagerung erfordert Zugriff auf world oder Datenduplexität
  bool render(); //kein const wegen selbstreferenz für shade

  //getter für Breite und höhe
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
  //
  std::string filename_;
};

#endif	/* _WORLD_HPP */

