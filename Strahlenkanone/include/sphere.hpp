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

class cube : public shape
{
public:
  bool intersect(ray& r, shade& rec);
};

#endif	/* _SPHERE_HPP */

