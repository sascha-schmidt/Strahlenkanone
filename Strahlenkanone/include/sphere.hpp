/* 
 * File:   sphere.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 17:04
 */

#ifndef _SPHERE_HPP
#define	_SPHERE_HPP

#include <shape.hpp>
#include <ray.hpp>
#include <shade.hpp>

class sphere : public shape
{
public:
  sphere(point3d c, double r, material m);
  sphere(double x, double y, double z, double r, material m);
  ~sphere();
  bool intersect(ray& r, shade& rec);

  bool translate(double x, double y, double z);
  bool scale(double x, double y, double z);
  bool rotatex(double angle);
  bool rotatey(double angle);
  bool rotatez(double angle);

private:
  point3d center_;
  double radius_;
};

#endif	/* _SPHERE_HPP */

