/* 
 * File:   shape_composite.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:09
 */

#ifndef _SHAPE_COMPOSITE_HPP
#define	_SHAPE_COMPOSITE_HPP


#include <vector>
#include <ray.hpp>
#include <shade.hpp>
#include <shape.hpp>


class shape_composite : public shape
{
public:
  shape_composite();
  ~shape_composite();
  bool intersect(ray& r, shade &rec);
private:
  std::vector<shape*> data_;
};

#endif	/* _SCOMPOSITE_HPP */

