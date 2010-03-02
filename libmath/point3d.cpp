#include <point3d.hpp>
#include <cassert>
#include <vector3d.hpp>

point3d::point3d ()
{
  data_[0] = 0.0;
  data_[1] = 0.0;
  data_[2] = 0.0;
  data_[3] = 1.0;   //homog. Koordi. bei Punkt immer 1
}

point3d::point3d (double x, double y, double z)
{
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
  data_[3] = 1.0;   //homog. Koordi. bei Punkt immer 1
}

point3d::~point3d ()
{
}

double&
point3d::operator[](unsigned index)
{
  assert(index <= 3); //inklusive homogener Erweiterung
  return data_[index];
}

double const&
point3d::operator[](unsigned index) const
{
  assert(index <= 3);
  return data_[index];
}

double
distance(point3d const& lhs, point3d const& rhs)
{
  vector3d tmp(lhs, rhs);
  return tmp.length();
}

point3d
operator+(point3d const& lhs, vector3d const& rhs)
{
  double a = lhs[0] + rhs[0];
  double b = lhs[1] + rhs[1];
  double c = lhs[2] + rhs[2];
  //vierte koordinate = 1 + 0 = 1 keine Anpassung nötig
  return point3d(a,b,c);
}

point3d
operator-(point3d const& lhs, vector3d const& rhs)
{
  double a = lhs[0] - rhs[0];
  double b = lhs[1] - rhs[1];
  double c = lhs[2] - rhs[2];
  //vierte koordinate = 0 + 1 = 1 keine Anpassung nötig
  return point3d(a,b,c);
}
