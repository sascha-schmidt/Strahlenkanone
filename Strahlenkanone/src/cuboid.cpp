#include "cuboid.hpp"
#include "point3d.hpp"
#include <vector3d.hpp>
#include <cassert>

cuboid::cuboid(point3d a, point3d b)
: fll_(a), bur_(b)
{
  assert(a[0] < b[0]);
  assert(a[1] < b[1]);
  assert(a[2] < b[2]);
}

bool
cuboid::intersect(ray& r, shade& rec)
{
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


  //to be continued
  
}