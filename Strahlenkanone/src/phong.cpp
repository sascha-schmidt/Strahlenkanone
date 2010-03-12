#include "phong.hpp"
#include "world.hpp"
#include <cmath>
#include <utility>
#include <iostream>

phong::phong()
: sc_(), lights_(), bg_(), ambient_()
{
}

void
phong::init(shape_composite sc, std::vector<light> l, rgb a, rgb b)
{
  sc_ = sc;
  lights_ = l;
  bg_ = b;
  ambient_ = a;
}

rgb
phong::color(ray view, shade const& s)
{
    rgb temp;
    rgb ka = s.material_ref.ka;
    rgb kd = s.material_ref.kd;
    rgb ks = s.material_ref.ks;
    double m = s.material_ref.m;
    //I_ip(λ) δ(l_i)
    temp[rgb::r] = ka[rgb::r] * ambient_[rgb::r];
    temp[rgb::g] = ka[rgb::g] * ambient_[rgb::g];
    temp[rgb::b] = ka[rgb::b] * ambient_[rgb::b];
    ray l;  //Strahl zur Lichtquelle
    l.ori = s.hitpoint;
    vector3d v = view.dir * (-1); //zum Betrachter
    v.normalize();
    for(std::vector<light>::iterator i = lights_.begin(); i != lights_.end(); std::advance(i,1))
    {
      l.dir = vector3d(s.hitpoint, (*i).pos);
      l.dir.normalize();
      //Ausgansstrahl:  r = 2 * (l·N) * N - l
      vector3d r =  (2 * dot(l.dir, s.n) * s.n) - l.dir;
      r.normalize();
      shade shadow; //wird nur für intersect benötigt
      sc_.intersect(l, shadow);
      double lichtabstand = vector3d(s.hitpoint, (*i).pos).length();
      //Beleuchtung nur, wenn kein Objekt zw. Licht und Punkt liegt
      if(!shadow.didhit || shadow.distance > lichtabstand)
      {
        float cosrv = dot(r, v);
        float cosln = dot(s.n, l.dir);
        //die cos müssen größer 0, weil es keine neg. Farben gibt
        //if(cosrv > 0 && cosln > 0)
        {
          cosrv = std::max(cosrv, 0.0f);
          cosln = std::max(cosln, 0.0f);
          //(kd(λ) cos ø_i + ks(λ) cos^m(ß_i))
          temp[rgb::r] += (*i).ld[rgb::r] * ((kd[rgb::r] * cosln) + (ks[rgb::r] * std::pow(cosrv, m)));
          temp[rgb::g] += (*i).ld[rgb::g] * ((kd[rgb::g] * cosln) + (ks[rgb::g] * std::pow(cosrv, m)));
          temp[rgb::b] += (*i).ld[rgb::b] * ((kd[rgb::b] * cosln) + (ks[rgb::b] * std::pow(cosrv, m)));
        }
      }
    }
    return temp;
}
