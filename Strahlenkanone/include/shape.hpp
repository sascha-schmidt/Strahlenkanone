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
#include <algorithm>

typedef std::pair<point3d, point3d> ppp;

//abstrakte Oberklasse für geometrische Objekte
class shape
{
public:
  shape():bbox_(), tform_(), mater_(){};
  shape(material m): bbox_(), tform_(), mater_(m){};
  ~shape(){}

  virtual bool intersect(ray& r, shade& rec)=0;

  material getmater() const; //getter für material

  virtual void bbox()=0;
  ppp getbbox() const;
  void setbbox(ppp b);
  bool bboxintersect(ray &r);

  virtual bool translate(double x, double y, double z)=0;
  virtual bool scale(double x, double y, double z)=0;
  virtual bool rotatex(double angle)=0;
  virtual bool rotatey(double angle)=0;
  virtual bool rotatez(double angle)=0;

private:
  //Bounding Box
  ppp bbox_;
  //Transformationsmatrix
  matrix tform_;
  material mater_;
};


#endif	/* _SHAPE_HPP */

