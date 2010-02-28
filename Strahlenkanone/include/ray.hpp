/* 
 * File:   ray.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:30
 */

#ifndef _RAY_HPP
#define	_RAY_HPP

#include <vector3d.hpp>

struct ray
{
  //Ursprung:
  point3d ori;
  //Richtung:
  vector3d dir;
};


#endif	/* _RAY_HPP */

