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
  cuboid(point3d a, point3d b, material m);
  cuboid(double x1,double y1,double z1,double x2,double y2,double z2, material m);
  ~cuboid();
  bool intersect(ray& r, shade& rec);

  void bbox();

  bool translate(double x, double y, double z);
  bool scale(double x, double y, double z);
  bool rotate (double a, double x, double y, double z);
  bool rotatex(double angle);
  bool rotatey(double angle);
  bool rotatez(double angle);

private:
  point3d fll_; // front lower left
  point3d bur_; // back upper right
};

#endif	/* _CUBOID_HPP */

