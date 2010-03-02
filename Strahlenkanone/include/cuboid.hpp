/* 
 * File:   cuboid.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:49
 */

#ifndef _CUBOID_HPP
#define	_CUBOID_HPP

#include <shape.hpp>
#include <ray.hpp>
#include <shade.hpp>
#include "point3d.hpp"

//Axis Aligned Box = achsenparalleler Quader
class cuboid : public shape
{
public:
  cuboid(point3d a, point3d b);
  bool intersect(ray& r, shade& rec);

private:
  point3d fll_; // front lower left
  point3d bur_; // back upper right
};

#endif	/* _CUBOID_HPP */

