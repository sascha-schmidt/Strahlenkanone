/* 
 * File:   light.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:23
 */

#ifndef _LIGHT_HPP
#define	_LIGHT_HPP

#include <point3d.hpp>
#include <rgb.hpp>

struct light
{
public:
  //Position
  point3d pos;
  //diffuse Leuchtstärke, farbspezifisch
  rgb ld;
};


#endif	/* _LIGHT_HPP */

