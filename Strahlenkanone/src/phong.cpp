#include "phong.hpp"
#include "world.hpp"
#include <cmath>
#include <utility>
#include <iostream>

#define MAX_DEPTH 4

phong::phong()
: sc_(), lights_(), bg_(), ambient_()
{
}

void
phong::init(shape_composite const& sc, std::vector<light> const& l, rgb const& a, rgb const& b)
{
  sc_ = sc;
  lights_ = l;
  bg_ = b;
  ambient_ = a;
}

rgb
phong::color(ray view, shade const& s) const
{
  if (s.material_ref.reflecting) //bei spiegelendem Material
  {
    return reflect(view, s, 0);
  }
  else  //Andernfalls Farbe nach Phong
  {
    rgb temp;
    rgb ka=s.material_ref.ka;
    rgb kd=s.material_ref.kd;
    rgb ks=s.material_ref.ks;
    double m=s.material_ref.m;
    //I_ip(λ) δ(l_i)
    temp[rgb::r]=ka[rgb::r] * ambient_[rgb::r];
    temp[rgb::g]=ka[rgb::g] * ambient_[rgb::g];
    temp[rgb::b]=ka[rgb::b] * ambient_[rgb::b];
    ray l; //Strahl zur Lichtquelle
    l.ori=s.hitpoint;
    vector3d v=view.dir * (-1); //zum Betrachter
    v.normalize();
    for (std::vector<light>::const_iterator i=lights_.begin(); i != lights_.end(); std::advance(i, 1))
    {
      l.dir=vector3d(s.hitpoint, (*i).pos);
      l.dir.normalize();
      //Ausgansstrahl:  r = 2 * (l·N) * N - l
      vector3d r=(2 * dot(l.dir, s.n) * s.n) - l.dir;
      r.normalize();
      shade shadow; //wird nur für intersect benötigt
      sc_.intersect(l, shadow);
      double lichtabstand=vector3d(s.hitpoint, (*i).pos).length();
      //Beleuchtung nur, wenn kein Objekt zw. Licht und Punkt liegt
      if (!shadow.didhit || shadow.distance > lichtabstand)
      {
        float cosrv=dot(r, v);
        float cosln=dot(s.n, l.dir);
        //die cos müssen größer 0, weil es keine neg. Farben gibt
        //if(cosrv > 0 && cosln > 0)
        {
          cosrv=std::max(cosrv, 0.0f);
          cosln=std::max(cosln, 0.0f);
          //(kd(λ) cos ø_i + ks(λ) cos^m(ß_i))
          temp[rgb::r]+=(*i).ld[rgb::r] * ((kd[rgb::r] * cosln) + (ks[rgb::r] * std::pow(cosrv, m)));
          temp[rgb::g]+=(*i).ld[rgb::g] * ((kd[rgb::g] * cosln) + (ks[rgb::g] * std::pow(cosrv, m)));
          temp[rgb::b]+=(*i).ld[rgb::b] * ((kd[rgb::b] * cosln) + (ks[rgb::b] * std::pow(cosrv, m)));
        }
      }
    }
    return temp;
  }
}

rgb
phong::reflect(ray view, shade const& s, unsigned depth) const
{
  if(depth > MAX_DEPTH) //Schwarz/bg_ bei zuvielen Spiegelungen
  {
    return bg_;
  }
  if(!s.material_ref.reflecting) //Wenn wir nicht weiter spiegeln: phong
  {
    return color(view,s);
  }
  else if(s.material_ref.reflecting) //Spiegelung der Spiegelung
  {
    ray ausfall; //view gespiegel an n = ausgehender Strahl
    ausfall.ori = s.hitpoint + 0.1 * s.n; //minimal verschiebung mal wieder
    //Spiegelung an n =  v - 2*(v*n)*n
    ausfall.dir = view.dir - (2 * dot(view.dir, s.n) * s.n);
    shade mir;
    sc_.intersect(ausfall, mir);
    if(mir.didhit)
    {
      //Wenn unser Ausfallsstrahl auf etwas trifft nehmen wir dessen Farbe
      return reflect(ausfall, mir, ++depth);
    }
    else //Wenn wir nichts treffen fliegt der Strahl ins unendliche
    {    //Also nehmen wir die Hintergrundfarbe
      return bg_;
    }
  }
}