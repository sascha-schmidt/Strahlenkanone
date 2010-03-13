/* 
 * File:   phong.hpp
 * Author: sascha
 *
 * Created on 7. März 2010, 19:10
 */

#ifndef _PHONG_HPP
#define	_PHONG_HPP

#include "rgb.hpp"
#include "shade.hpp"
#include <vector>
#include "light.hpp"
#include "shape_composite.hpp"

class phong
{
public:
  phong();
  void init(shape_composite sc, std::vector<light> l, rgb a, rgb b);
  rgb color(ray view, shade const& s);
  //Für mit Spiegelung
  rgb color(ray view, shade const& s, unsigned const& depth);

private:
  //Vector mit allen Lichtern
  std::vector<light> lights_;
  shape_composite sc_;
  rgb ambient_;
  rgb bg_;
};


#endif	/* _PHONG_HPP */

