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


class cuboid : public shape
{
public:
  bool intersect(ray& r, shade& rec);
};

#endif	/* _CUBOID_HPP */

