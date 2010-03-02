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
  bool intersect(ray& r, shade& rec);

private:
  point3d center_;
  double radius_;
};

#endif	/* _SPHERE_HPP */

