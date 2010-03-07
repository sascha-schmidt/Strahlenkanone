#include "phong.hpp"
#include "world.hpp"

rgb
phong::color(shade const& s)
{
    double r,g,b;
    rgb amb = s.world_ptr->getambient();
    
    rgb ka = s.material_ref.ka;
    rgb kd = s.material_ref.kd;
    rgb ks = s.material_ref.ks;
    double m = s.material_ref.m;
    r = ka[rgb::r] * amb[rgb::r];
    g = ka[rgb::g] * amb[rgb::g];
    b = ka[rgb::b] * amb[rgb::b];

    return rgb(r,g,b);
}
