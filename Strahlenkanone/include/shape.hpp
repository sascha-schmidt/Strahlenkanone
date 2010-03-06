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
  shape();
  shape(material const& m);
  ~shape();

  virtual bool intersect(ray& r, shade& rec)=0;

  material getmater() const; //getter für material

  virtual void bbox()=0;
  ppp getbbox() const;
  void setbbox(ppp b);
  bool bboxintersect(ray r); //ray per Kopie für transform

  matrix const& gettform() const;
  matrix const& gettformi()  const;
  void settform(matrix m);

  virtual bool translate(double x, double y, double z)=0;
  virtual bool scale(double x, double y, double z)=0;
  virtual bool rotate (double a, double x, double y, double z)=0;
  virtual bool rotatex(double angle)=0;
  virtual bool rotatey(double angle)=0;
  virtual bool rotatez(double angle)=0;

private:
  //Bounding Box
  ppp bbox_;
  //Transformationsmatrix
  matrix tform_;
  matrix tformi_;
  material mater_;
};


#endif	/* _SHAPE_HPP */

