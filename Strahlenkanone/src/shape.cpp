#include "shape.hpp"

shape::shape()
:bbox_(), tform_(), mater_()
{}

shape::shape(material const& m)
: bbox_(), tform_(), mater_(m){}

shape::~shape()
{}


material
shape::getmater() const
{
  return mater_;
}

ppp
shape::getbbox() const
{
  return bbox_;
}

void
shape::setbbox(ppp b)
{
  bbox_ = b;
}

bool
shape::bboxintersect(ray r)
{
  if(tform_ != matrix()) //Wenn es sich nicht um die Einheitsmatrix handelt
  {
    r.ori = tform_ * r.ori;     //transformation auf den Ray anwenden
    r.dir = tform_ * r.dir;
  }
  //s. cuboid.cpp
  vector3d tmin(0.0, 0.0, 0.0);
  vector3d tmax(0.0, 0.0, 0.0);
  //für x:
  //Division durch Richtungsvektor um Faktor für diesen zu erhalten
  double x_inv = 1.0/ r.dir[0];
  //Unterscheidung aus welcher Richtung wir kommen

  if(x_inv >= 0) // "von vorne"
  {
    //der kleinste Faktor ist der Abstand zum Cuboid durch den Vektor(mal x_inv)
    //um Faktor zu erhalten
    tmin[0] = (bbox_.first[0] - r.ori[0]) * x_inv;
    //der größte is der Abstand zur "Rückwand"
    tmax[0] = (bbox_.second[0] - r.ori[0]) * x_inv;
  }
  else //"von hinten"
  {
    //wie oben nur das Rückseite näher am Strahlursprung ist
    tmin[0] =  (bbox_.second[0] - r.ori[0]) * x_inv;
    //und Vorderseite weiter weg
    tmax[0] =  (bbox_.first[0] - r.ori[0]) * x_inv;
  }

  //für y:
  double y_inv = 1.0/ r.dir[1];
  if(y_inv >= 0)
  {
    tmin[1] = (bbox_.first[1] - r.ori[1]) * y_inv;
    tmax[1] = (bbox_.second[1] - r.ori[1]) * y_inv;
  }
  else
  {
    tmin[1] =  (bbox_.second[1] - r.ori[1]) * y_inv;
    tmax[1] =  (bbox_.first[1] - r.ori[1]) * y_inv;
  }
  //für z:
  double z_inv = 1.0/ r.dir[2];
  if(z_inv >= 0)
  {
    tmin[2] = (bbox_.first[2] - r.ori[2]) * z_inv;
    tmax[2] = (bbox_.second[2] - r.ori[2]) * z_inv;
  }
  else
  {
    tmin[2] =  (bbox_.second[2] - r.ori[2]) * z_inv;
    tmax[2] =  (bbox_.first[2] - r.ori[2]) * z_inv;
  }
  //Bestimmung der Schnittseite -> Normalenvektor:
  //größter Faktor in tmin = Faktor beim Betreten der Box
  double tminmax = std::max(tmin[0], std::max(tmin[1], tmin[2]));
  //kleinster Faktor in tmax = Faktor beim Verlassen
  double tmaxmin = std::min(tmax[0], std::min(tmax[1], tmax[2]));

  if(tmaxmin > 0 && tminmax < tmaxmin) //Überlappen sich die slopes?
  {                                    //= Strahl schneidet Box
    return (true);
  }
  return (false);
}

matrix const&
shape::gettform() const
{
  return tform_;
}

matrix const&
shape::gettformi() const
{
  return tformi_;
}

void
shape::settform(matrix m)
{
  tform_ = m;
  m.invert();
  tformi_ = m;
}