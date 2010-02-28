/* 
 * File:   material.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:19
 */

#ifndef _MATERIAL_HPP
#define	_MATERIAL_HPP

#include <rgb.hpp>

struct material //nach phong
{
public:
  //ambienter Koeffizient
  rgb ka;
  //diffuser Koeffizient
  rgb kd;
  //spekularer Koeffizient
  rgb ks;
  //Spiegelungsexponent
  float m;
};

#endif	/* _MATERIAL_HPP */

