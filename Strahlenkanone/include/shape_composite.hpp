/* 
 * File:   shape_composite.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:09
 */

#ifndef _SHAPE_COMPOSITE_HPP
#define	_SHAPE_COMPOSITE_HPP

#include <shape.hpp>
#include <vector>

using namespace std;

class shape_composite : public shape
{
public:
  shape_composite();
  ~shape_composite();
  bool intersect(ray& r, shade& rec);
private:
  vector<shape*> data_;
};

#endif	/* _SHAPE_COMPOSITE_HPP */

