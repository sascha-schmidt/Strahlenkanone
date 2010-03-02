#include "triangle.hpp"
#include <math.h>
#include <vector3d.hpp>

bool
triangle::intersect(ray& r, shade& rec)
{
  //Als erstes brauchen wir den normalen Vektor
  vector3d eineseite(a_, b_);
  vector3d andereseite(a_, c_);
  vector3d /*un*/normal = cross(eineseite, andereseite);
  normal.normalize();
  
  //Schnittpunkt des Strahl mit der imaginären Ebene in der das 3eck liegt
  //für die HNF(P*N +d = 0) brauchen wir noch d
  double d = dot(a_, normal);
  if(d < 0){d *= -1;} //anstatt Betrag
  //stellt man die HNF nach dem Faktor um ergibt sich
  // -(P0 * N +d)/V*N
  double fak = dot(r.ori,normal) + d;
  fak *= -1;
  fak /= dot(r.dir, normal);
  if(fak < 0){return (false);} // = Ebene liegt hinterm Strahlurpsrung
  //Der Punkt:
  point3d p = r.ori + (fak * r.dir);

  //Liegt der Punkt im Dreieck?
  //Mit baryzentrischen Koordinaten
  //Koordinatensystem im Dreieck mit Ursprung in one_
  //Basisvektoren:
  //entlang der Seite a->b
  vector3d i(a_,c_);
  //entlang der Seite one->two
  vector3d j(a_,b_);
  //Zielvektor zu p
  vector3d  z(a_, p);
  //dotprodukte
  double doti(dot(i,i));
  double dotij(dot(i,j));
  double dotiz(dot(i,z));
  double dotj(dot(j,j));
  double dotjz(dot(j,z));
  //zum normalisieren im Vektorraum:
  double n(1/(doti * dotj - dotij * dotij));
  //Länge des Vektors entlang i
  double u(n * (dotj * dotiz - dotij * dotjz));
  //Länge des Vektors entlang j
  double v(n * (doti * dotjz - dotij * dotiz));
  //Vorrausetzung dafür, dass p im Dreieck liegt:
  //u und v positiv also p zwischen den beiden Seiten/Vektoren
  //u + v, also die Entfernung, kleiner als Länger der Vektoren(1)
  bool is_inside =(u > 0) && (v > 0) && ((u + v) <= 1);
  if(!is_inside){return (false);}

  //Speichern der gewonnen Informationen
  //Nur wenn das der erste oder der vorderste Treffer ist
  if(!rec.didhit || distance(r.ori, p) < rec.distance)
  {
    rec.didhit = true; //Juchu getroffen
    rec.material_ref = getmater();
    rec.hitpoint = p;
    rec.n = normal;
  }
}
