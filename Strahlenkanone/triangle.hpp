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
  bool intersect(ray& r, shade& rec);

private:
  point3d c_;
};


#endif	/* _TRIANGLE_HPP */

