#include "sphere.hpp"
#include "material.hpp"
#include <math.h>

bool
sphere::intersect(ray& r, shade& rec)
{ //Nach http://www.cs.princeton.edu/courses/archive/fall00/cs426/lectures/raycast/sld013.htm
  //Vector vom Strahlenursprung zum Mittelpunkt
  vector3d abstand(r.ori, center_);
  //Faktor der der Länge des Abstandes auf dem Strahl entspricht
  double m = dot(abstand, r.dir);
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
  point3d P1 = r.ori + (fak1 * r.dir);
  point3d P2 = r.ori + (fak2 * r.dir);
  //Der Schnittpunkt näher am Strahlenurpsrung ist, ist der Gesuchte
  point3d Pmin;
  if(distance(r.ori, P1) < distance(r.ori, P2)){Pmin = P1;}
  else{Pmin = P2;}
  
  //Speichern der gewonnen Informationen
  //Nur wenn das der erste oder der vorderste Treffer ist
  if(!rec.didhit || distance(r.ori, Pmin) < rec.distance)
  {
    rec.didhit = true; //Juchu getroffen
    rec.material_ref = getmater();
    rec.hitpoint = Pmin;
    vector3d normal(center_, Pmin);
    normal.normalize();
    rec.n = normal;
  }
  return (true);
}
