#include <vector3d.hpp>
#include <point3d.hpp>

#include <iomanip>                // std::fixed, std::setprecision
#include <ostream>                // std::ostream
#include <cassert>
#include <cmath>


vector3d::vector3d ()
{
  data_[0] = 0.0;
  data_[1] = 0.0;
  data_[2] = 0.0;
  data_[3] = 0.0;   //homog. Koordi. bei Vektor immer 0
}

vector3d::vector3d (double x, double y, double z)
{
  data_[0] = x;
  data_[1] = y;
  data_[2] = z;
  data_[3] = 0.0;   //homog. Koordi. bei Vektor immer 0
}

vector3d::vector3d (point3d const& eins, point3d const& zwei)
{
  data_[0] = (zwei[0] - eins[0]);
  data_[1] = (zwei[1] - eins[1]);
  data_[2] = (zwei[2] - eins[2]);
  data_[3] = 0.0;   //homog. Koordi. bei Vektor immer 0
}

vector3d::~vector3d ()
{ //alles im Stack
}


double&
vector3d::operator[](unsigned index)
{
  assert(index <= 3); //inklusive homogener Erweiterung
  return data_[index];
}

double const&
vector3d::operator[](unsigned index) const
{
  assert(index <= 3);
  return data_[index];
}

double
vector3d::length () const
{
  //sqrt(x² + y² +z² + 0²)
  return sqrt(pow(data_[0], 2) + pow(data_[1], 2) + pow(data_[2],2)); //+ 0²
}

void
vector3d::normalize ()
{
  assert(length() != 0);
  double l = length(); //spart Berechnung
  data_[0] /= l;
  data_[1] /= l;
  data_[2] /= l;
  //4rte Kooridnate 0-> 0/l => 0
}

double dot(vector3d const& lhs, vector3d const& rhs)
{
  return ((lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]));
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

double dot(point3d const& lhs, vector3d const& rhs)
{
  return ((lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]));
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

double dot(vector3d const& lhs, point3d const& rhs)
{
  return ((lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]));
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

vector3d
cross(vector3d const& lhs, vector3d const& rhs)
{
  //
  double a = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
  double b = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
  double c = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
  return vector3d(a, b, c);
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

vector3d
cross(point3d const& lhs, vector3d const& rhs)
{
  //
  double a = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
  double b = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
  double c = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
  return vector3d(a, b, c);
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

vector3d
cross(vector3d const& lhs, point3d const& rhs)
{
  //
  double a = (lhs[1] * rhs[2]) - (lhs[2] * rhs[1]);
  double b = (lhs[2] * rhs[0]) - (lhs[0] * rhs[2]);
  double c = (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
  return vector3d(a, b, c);
  //da 4rte Koordinate 0 muss sie nicht berücksichtig werden
}

vector3d&
vector3d::operator += (vector3d const& rhs)
{
  data_[0] += rhs.data_[0];
  data_[1] += rhs.data_[1];
  data_[2] += rhs.data_[2];
  // 0 + 0 = 0
  return *this;
}

vector3d&
vector3d::operator -= (vector3d const& rhs)
{
  data_[0] -= rhs.data_[0];
  data_[1] -= rhs.data_[1];
  data_[2] -= rhs.data_[2];
  // 0 - 0 = 0
  return *this;
}

vector3d&
vector3d::operator*=(double skalar)
{
  data_[0] *= skalar;
  data_[1] *= skalar;
  data_[2] *= skalar;
  // 0 * skalar = 0
  return *this;
}

vector3d
operator+(vector3d const& lhs, vector3d const& rhs)
{
  vector3d temp(lhs[0], lhs[1], lhs[2]);
  temp += rhs;
  return temp;
}


vector3d
operator-(vector3d const& lhs, vector3d const& rhs)
{
  vector3d temp(lhs[0], lhs[1], lhs[2]);
  temp -= rhs;
  return temp;
}

vector3d
operator*(double lhs, vector3d const& rhs)
{
  return vector3d((rhs[0] * lhs), (rhs[1] * lhs), (rhs[2] * lhs));
}

vector3d
operator*(vector3d const& lhs, double rhs)
{
    return vector3d((lhs[0] * rhs), (lhs[1] * rhs), (lhs[2] * rhs));
}

std::ostream&
operator<<(std::ostream& os, vector3d const& a)
{
  std::ostream::sentry const cerberus(os);

  if (cerberus) {
    os << std::fixed << std::setprecision(3)
       << '['
       << a[0] << ','
       << a[1] << ','
       << a[2] << ','
       << a[3] 
       << ']'
       << std::endl;
  }

  return os;
}
