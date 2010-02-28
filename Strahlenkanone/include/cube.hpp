/* 
 * File:   cube.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:54
 */

#ifndef _CUBE_HPP
#define	_CUBE_HPP

#include <shape.hpp>
#include <ray.hpp>
#include <shade.hpp>

class cube : public shape
{
public:
  bool intersect(ray& r, shade& rec);
};


#endif	/* _CUBE_HPP */

