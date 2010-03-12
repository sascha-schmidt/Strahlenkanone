#include "sphere.hpp"
#include "material.hpp"
#include <math.h>
#include <iostream>

sphere::sphere(point3d c, double r, material const& m)
: center_(c), radius_(r), shape(m)
{
  bbox();
}

sphere::sphere(double x, double y, double z, double r, material const& m)
: center_(point3d(x,y,z)), radius_(r), shape(m)
{
  bbox();
}

sphere::~sphere()
{
}

bool
sphere::intersect(ray r, shade& rec)
{
  if(gettform() != matrix()) //Wenn es sich nicht um die Einheitsmatrix handelt
  {
    r.ori = gettform() * r.ori;     //transformation auf den Ray anwenden
    r.dir = gettform() * r.dir;
    //std::cout << "transf. matrix in sphere::intersect detected" << std::endl;
  }
  //Nach http://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld013.htm
  //Vector vom Strahlenursprung zum Mittelpunkt
  vector3d abstand(r.ori, center_);
  //Faktor der der Länge des Abstandes auf dem Strahl entspricht
  double m = dot(abstand, r.dir);
  if(m < 0.001){return (false);} //Sphere liegt hinter Strahlenursprung
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
  point3d P1 = r.ori + (fak1 * r.dir);
  point3d P2 = r.ori + (fak2 * r.dir);
  //Der Schnittpunkt näher am Strahlenurpsrung ist, ist der Gesuchte
  point3d Pmin;
  if(distance(r.ori, P1) < distance(r.ori, P2)){Pmin = P1;}
  else{Pmin = P2;}
  
  //Speichern der gewonnen Informationen
  //Nur wenn das der erste oder der vorderste Treffer ist
  if(distance(r.ori, Pmin) < rec.distance)
  {
    rec.didhit = true; //Juchu getroffen
    rec.material_ref = getmater();
    vector3d normal(center_, Pmin);
    rec.hitpoint = Pmin;
    if(gettform() != matrix())
    {
      //Rückstranformation der Normalen
      matrix back = gettformi();
      back.transpose();
      normal = back * normal;
      //Tranformation des Hitpoints
      rec.hitpoint = gettformi() * rec.hitpoint;
    }
    normal.normalize();
    rec.hitpoint = rec.hitpoint + 0.01 * normal;//minimal Verschiebung verhindert Schnitt mit sich selbst
    rec.n = normal;
    //TODO: Stimmt die Distance ?!?
    rec.distance = distance(r.ori, Pmin);
    return (true);
  }
  return (false);
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
  temp.first = gettform() * temp.first;
  temp.second = gettform() * temp.second;
  setbbox(temp);
}