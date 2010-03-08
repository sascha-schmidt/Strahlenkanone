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
#include <vector>
#include "light.hpp"

class phong
{
public:
  //phong( bla bla);
  rgb color(shade const& s);

private:
  //Vector mit allen Lichtern
  std::vector<light> lights_;
  rgb ambient_;
  rgb bg_;
};


#endif	/* _PHONG_HPP */

