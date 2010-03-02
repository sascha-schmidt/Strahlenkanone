/* 
 * File:   shape.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 16:01
 */

#ifndef _SHAPE_HPP
#define	_SHAPE_HPP

#include <ray.hpp>
#include <matrix.hpp>
#include <shade.hpp>
#include <point3d.hpp>
#include <utility>

//abstrakte Oberklasse für geometrische Objekte
class shape
{
public:
  virtual bool intersect(ray& r, shade& rec)=0;

  material getmater(){return mater_;};

private:
  //Bounding Box
  std::pair<point3d, point3d> bbox_;
  //Transformationsmatrix
  matrix tform_;
  material mater_;
};


#endif	/* _SHAPE_HPP */

