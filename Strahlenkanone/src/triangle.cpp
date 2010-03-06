#include "triangle.hpp"
#include <math.h>
#include <vector3d.hpp>
#include <iostream>

triangle::triangle(point3d q, point3d w, point3d e, material const& m)
: a_(q), b_(w), c_(e), shape(m)
{
  bbox();
}

triangle::triangle(double x1, double x2, double x3, double y1, double y2,
                   double y3, double z1, double z2, double z3, material const& m)
: a_(point3d(x1,y1,z1)), b_(point3d(x1,y1,z1)), c_(point3d(x1,y1,z1)), shape(m)
{
  bbox();
}

triangle::~triangle()
{
}

bool
triangle::intersect(ray& r, shade& rec)
{

//  if(bboxintersect(r))
//  {
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
      return (true);
    }
//  }
  return (false);
}


bool
triangle::translate(double x, double y, double z)
{
  matrix temp;
  temp = make_translation(x,y,z);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

bool
triangle::scale(double x, double y, double z)
{
  matrix temp;
  temp = make_scale(x,y,z);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

bool
triangle::rotate(double a, double x, double y, double z)
{
  matrix temp;
  temp = make_rotation(a, x ,y ,z);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

bool
triangle::rotatex(double angle)
{
  matrix temp;
  temp = make_rotation_x(angle);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

bool
triangle::rotatey(double angle)
{
  matrix temp;
  temp = make_rotation_y(angle);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

bool
triangle::rotatez(double angle)
{
  matrix temp;
  temp = make_rotation_z(angle);
  a_ = temp * a_;
  b_ = temp * b_;
  c_ = temp * c_;
  bbox();
  return (true);
}

void
triangle::bbox()
{
  point3d mini;
  point3d maxi;
  ppp temp;
  mini[0] = std::min(a_[0], std::min(b_[0], c_[0]));
  mini[0] = std::min(a_[1], std::min(b_[1], c_[1]));
  mini[0] = std::min(a_[2], std::min(b_[2], c_[2]));
  maxi[0] = std::max(a_[0], std::max(b_[0], c_[0]));
  maxi[0] = std::max(a_[1], std::max(b_[1], c_[1]));
  maxi[0] = std::max(a_[2], std::max(b_[2], c_[2]));
  temp.first = mini;
  temp.second = maxi;
  setbbox(temp);
}