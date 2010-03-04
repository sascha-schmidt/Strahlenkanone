/* 
 * File:   triangle.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:56
 */

#ifndef _TRIANGLE_HPP
#define	_TRIANGLE_HPP

#include <shape.hpp>
#include <vector3d.hpp>
#include <ray.hpp>
#include <shade.hpp>

class triangle : public shape
{
public:
  triangle(point3d q, point3d w, point3d e, material m);
  triangle(double x1, double x2, double x3, double y1, double y2, double y3
          , double z1, double z2, double z3, material m);
  ~triangle();
  bool intersect(ray& r, shade& rec);

  void bbox();

  bool translate(double x, double y, double z);
  bool scale(double x, double y, double z);
  bool rotatex(double angle);
  bool rotatey(double angle);
  bool rotatez(double angle);

private:
  point3d a_;
  point3d b_;
  point3d c_;
};


#endif	/* _TRIANGLE_HPP */

