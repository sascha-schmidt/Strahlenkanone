#include "sphere.hpp"
#include "material.hpp"
#include <math.h>
#include <iostream>

sphere::sphere(point3d c, double r, material m)
: center_(c), radius_(r), shape(m)
{
  bbox();
}

sphere::sphere(double x, double y, double z, double r, material m)
: center_(point3d(x,y,z)), radius_(r), shape(m)
{
  bbox();
}

bool
sphere::intersect(ray& r, shade& rec)
{   //if(bboxintersect(r)) nicht nötig, weil so genauso schnell
  ray strahl = r;
  if(gettform() != matrix()) //Wenn es sich nicht um die Einheitsmatrix handelt
  {
    strahl.ori = gettform() * r.ori;     //transformation auf den Ray anwenden
    strahl.dir = gettform() * r.dir;
    std::cout << "transf. matrix in sphere::intersect detected" << std::endl;
  }
  //Nach http://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld013.htm
  //Vector vom Strahlenursprung zum Mittelpunkt
  vector3d abstand(strahl.ori, center_);
  //Faktor der der Länge des Abstandes auf dem Strahl entspricht
  double m = dot(abstand, strahl.dir);
  if(m < 0){return (false);} //Sphere liegt hinter Strahlenursprung
  //Abstand Strahl<-> Mittelpunkt nach Phytagoras(hier zum Quadrat)
  double distquad = dot(abstand, abstand) - (m * m); //brauchen nur das Quadrat
  double radiusquad = radius_ * radius_; //besser als Wurzel ziehen
  //Wenn der Abstand zum Mittelpunkt größer als der Radius ist, dann schneiden
  if(distquad > radiusquad) {return (false);} //sie sich nicht
  
  //Schnittpunktberechnung:

  //Abstand von m zu einem der Schnittpunkte
  double n = sqrt(radiusquad - distquad);
  //2 Faktoren für 2 Schnittpunkte
  double fak1 = m - n;
  double fak2 = m + n;
  //Schnittpunkte:
  point3d P1 = strahl.ori + (fak1 * strahl.dir);
  point3d P2 = strahl.ori + (fak2 * strahl.dir);
  //Der Schnittpunkt näher am Strahlenurpsrung ist, ist der Gesuchte
  point3d Pmin;
  if(distance(strahl.ori, P1) < distance(strahl.ori, P2)){Pmin = P1;}
  else{Pmin = P2;}
  
  //Speichern der gewonnen Informationen
  //Nur wenn das der erste oder der vorderste Treffer ist
  if(!rec.didhit || distance(strahl.ori, Pmin) < rec.distance)
  {
    rec.didhit = true; //Juchu getroffen
    rec.material_ref = getmater();
    rec.hitpoint = Pmin;
    vector3d normal(center_, Pmin);
    if(gettform() != matrix())
    {
      matrix back = gettformi();
      back.transpose();
      normal = back * normal;
    }
    normal.normalize();
    rec.n = normal;
    return (true);
  }
  return (false);
}

bool
sphere::translate(double x, double y, double z)
{
  settform(make_translation(x,y,z));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

bool
sphere::scale(double x, double y, double z)
{
  settform(make_scale(x,y,z));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

bool
sphere::rotate(double a, double x, double y, double z)
{
  settform(make_rotation(a, x ,y ,z));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

bool
sphere::rotatex(double angle)
{
  settform(make_rotation_x(angle));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

bool
sphere::rotatey(double angle)
{
  settform(make_rotation_y(angle));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

bool
sphere::rotatez(double angle)
{
  settform(make_rotation_z(angle));
  //bbox(); nicht nötig tform_ wird bei bboxintersect berücksichtig
  return (true);
}

void
sphere::bbox()
{
  point3d mini;
  point3d maxi;
  ppp temp;
  mini[0] = center_[0] - radius_;
  mini[1] = center_[1] - radius_;
  mini[2] = center_[2] - radius_;
  maxi[0] = center_[0] + radius_;
  maxi[1] = center_[1] + radius_;
  maxi[2] = center_[2] + radius_;
  temp.first = mini;
  temp.second = maxi;
  setbbox(temp);
}