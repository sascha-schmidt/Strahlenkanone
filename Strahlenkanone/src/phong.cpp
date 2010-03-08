#include "phong.hpp"
#include "world.hpp"

rgb
phong::color(shade const& s)
{
//    double r,g,b;
//    rgb amb = s.world_ptr->getambient();
//
//    rgb ka = s.material_ref.ka;
//    rgb kd = s.material_ref.kd;
//    rgb ks = s.material_ref.ks;
//    double m = s.material_ref.m;
//    r = ka[rgb::r] * amb[rgb::r];
//    g = ka[rgb::g] * amb[rgb::g];
//    b = ka[rgb::b] * amb[rgb::b];
//    std::vector<light> lights = s.world_ptr->lights_;
//    shape_composite sc = s.world_ptr->master_;
//    ray strahl;
//    strahl.ori = s.hitpoint;
//    for(std::vector<light>::iterator i = lights.begin(); i != lights.end(); std::advance(i,1))
//    {
//      shade sha;
//      strahl.dir = vector3d(s.hitpoint, (*i).pos);
//      if(!sc.intersect(strahl, sha))
//      {
//        //erstmal nur diffus
//        r += (*i).ld[rgb::r] * (kd[rgb::r] * dot(strahl.dir, s.n) /*+  bla*/);
//        g += (*i).ld[rgb::g] * (kd[rgb::g] * dot(strahl.dir, s.n) /*+  bla*/);
//        b += (*i).ld[rgb::b] * (kd[rgb::b] * dot(strahl.dir, s.n) /*+  bla*/);
//      }
//
//    }
//
//    return rgb(r,g,b);
}
