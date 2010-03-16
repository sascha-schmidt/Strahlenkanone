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

  virtual bool intersect(ray r, shade& rec)const=0;

  material getmater() const; //getter für material

  //erstell in abgeleiteten Klassen eine bbox
  virtual void bbox()=0;
  //setter und getter für bbox
  virtual ppp getbbox() const;
  virtual void setbbox(ppp b);
  //testet ob bbox intersected, ausschlielich beim composite
  bool bboxintersect(ray r) const; //ray per Kopie für transform

  //getter für die tranformationsmatrix, alternativ protetected, aber abgleitete
  //Klassen müssen die matrix nicht ändern, deswegen lieber getter

  // virtual weil shape_composite diese Funktionen überschreiben muss
  
  virtual matrix const& gettform() const;
  virtual matrix const& gettformi()  const;

  //Transformationen

  // virtual weil shape_composite diese Funktionen überschreiben muss
  virtual bool translate(double x, double y, double z);
  virtual bool scale(double x, double y, double z);
  virtual bool rotate (double a, double x, double y, double z);
  virtual bool rotatex(double angle);
  virtual bool rotatey(double angle);
  virtual bool rotatez(double angle);

private:
  //Bounding Box
  ppp bbox_;
  //Transformationsmatrix
  matrix tform_;
  matrix tformi_;
  material mater_;
};


#endif	/* _SHAPE_HPP */

