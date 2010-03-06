#include "cuboid.hpp"
#include "point3d.hpp"
#include <vector3d.hpp>
#include <cassert>
#include <algorithm>
#include <matrix.hpp>

cuboid::cuboid(point3d a, point3d b, material const& m)
: fll_(a), bur_(b), shape(m)
{
  assert(a[0] < b[0]);
  assert(a[1] < b[1]);
  assert(a[2] < b[2]);
  bbox();
}

cuboid::cuboid(double x1,double y1,double z1,double x2,double y2,double z2, material const& m)
: fll_(point3d(x1,y1,z1)), bur_(point3d(x2,y2,z2)), shape(m)
{
  assert(fll_[0] < bur_[0]);
  assert(fll_[1] < bur_[1]);
  assert(fll_[2] < bur_[2]);
  bbox();
}

bool
cuboid::intersect(ray& r, shade& rec)
{
  //if(bboxintersect(r)) nicht nötig, weil so genauso schnell
  //Berechnung mittels slopes
  //Begrenzung des Richtungsvektors auf den Wertebereich des Cuboid durch
  //Einschränkung der Faktoren für jede Koordinate einzeln
  //Speicherung des max. und min. Faktors für jede Koordinate in Vektor
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
    tmin[0] = (fll_[0] - r.ori[0]) * x_inv;
    //der größte is der Abstand zur "Rückwand"
    tmax[0] = (bur_[0] - r.ori[0]) * x_inv;
  }
  else //"von hinten"
  {
    //wie oben nur das Rückseite näher am Strahlursprung ist
    tmin[0] =  (bur_[0] - r.ori[0]) * x_inv;
    //und Vorderseite weiter weg
    tmax[0] =  (fll_[0] - r.ori[0]) * x_inv;
  }

  //für y:
  double y_inv = 1.0/ r.dir[1];
  if(y_inv >= 0)
  {
    tmin[1] = (fll_[1] - r.ori[1]) * y_inv;
    tmax[1] = (bur_[1] - r.ori[1]) * y_inv;
  }
  else
  {
    tmin[1] =  (bur_[1] - r.ori[1]) * y_inv;
    tmax[1] =  (fll_[1] - r.ori[1]) * y_inv;
  }
  //für z:
  double z_inv = 1.0/ r.dir[2];
  if(z_inv >= 0)
  {
    tmin[2] = (fll_[2] - r.ori[2]) * z_inv;
    tmax[2] = (bur_[2] - r.ori[2]) * z_inv;
  }
  else
  {
    tmin[2] =  (bur_[2] - r.ori[2]) * z_inv;
    tmax[2] =  (fll_[2] - r.ori[2]) * z_inv;
  }


  //Bestimmung der Schnittseite -> Normalenvektor:
  //größter Faktor in tmin = Faktor beim Betreten der Box
  double tminmax = std::max(tmin[0], std::max(tmin[1], tmin[2]));
  //kleinster Faktor in tmax = Faktor beim Verlassen
  double tmaxmin = std::min(tmax[0], std::min(tmax[1], tmax[2]));

  point3d p(0,0,0);
  vector3d normal(0,0,0);
  if(tmaxmin > 0 && tminmax < tmaxmin) //Überlappen sich die slopes?
  {                                    //= Strahl schneidet Box
    if(tminmax > 0) //Strahl kommt von außerhalb
    {
      p = r.ori + (tminmax * r.dir);
      //Bestimmung des Normalenvektors:
      if(tmin[0] == tminmax && x_inv >= 0.0){normal[0] = -1;}     // -x
      if(tmin[0] == tminmax && x_inv < 0.0){normal[0] =   1;}     // +x
      if(tmin[1] == tminmax && y_inv >= 0.0){normal[1] = -1;}     // -y
      if(tmin[1] == tminmax && y_inv < 0.0){normal[1] =   1;}     // +y
      if(tmin[2] == tminmax && z_inv >= 0.0){normal[2] = -1;}     // -z
      if(tmin[2] == tminmax && z_inv < 0.0){normal[2] =   1;}     // +z
    }
    else  //Strahlursprung liegt in der Box
    {
      p = r.ori + (tmaxmin * r.dir);
      //Bestimmung des Normalenvektors:
      //wie oben nur umgedreht, da der Stehl die Box verlässt und der normalen
      //Vektor damit in die Box zeigt
      if(tmin[0] == tminmax && x_inv >= 0.0){normal[0] = 1;}   //   +x
      if(tmin[0] == tminmax && x_inv < 0.0){normal[0] = -1;}     // -x
      if(tmin[1] == tminmax && y_inv >= 0.0){normal[1] = 1;}  //    +y
      if(tmin[1] == tminmax && y_inv < 0.0){normal[1] = -1;}    //  -y
      if(tmin[2] == tminmax && z_inv >= 0.0){normal[2] = 1;}  //    +z
      if(tmin[2] == tminmax && z_inv < 0.0){normal[2] = -1;}    //  -z
    }
  }
  //das heißt noch lange nicht, das es der naheliegendste Schnittpunkt ist
  if(!rec.didhit || distance(r.ori, p) < rec.distance)
  {
    rec.didhit = true; //Juchu getroffen
    rec.material_ref = getmater();
    rec.hitpoint = p;
    rec.n = normal;
    return (true);
  }
 return (false);
}


bool
cuboid::translate(double x, double y, double z)
{
  matrix temp;
  temp = make_translation(x,y,z);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

bool
cuboid::scale(double x, double y, double z)
{
  matrix temp;
  temp = make_scale(x,y,z);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

bool
cuboid::rotate(double a, double x, double y, double z)
{
  matrix temp;
  temp = make_rotation(a, x, y, z);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

bool
cuboid::rotatex(double angle)
{
  matrix temp;
  temp = make_rotation_x(angle);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

bool
cuboid::rotatey(double angle)
{
  matrix temp;
  temp = make_rotation_y(angle);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

bool
cuboid::rotatez(double angle)
{
  matrix temp;
  temp = make_rotation_z(angle);
  fll_ = temp * fll_;
  bur_ = temp * bur_;
  bbox();
  return true;
}

void
cuboid::bbox()
{
  ppp temp;
  temp.first = fll_;
  temp.second = bur_;
  setbbox(temp);
}