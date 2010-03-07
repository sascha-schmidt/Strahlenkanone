/* 
 * File:   phong.hpp
 * Author: sascha
 *
 * Created on 7. März 2010, 19:10
 */

#ifndef _PHONG_HPP
#define	_PHONG_HPP

#include "rgb.hpp"
#include "shade.hpp"

class phong
{
public:
  rgb color(shade const& s);
};


#endif	/* _PHONG_HPP */

