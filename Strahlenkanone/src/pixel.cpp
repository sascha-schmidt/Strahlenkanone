// header i/f
#include "pixel.hpp"

// header, system
#include <ostream> 


pixel::pixel(std::size_t a, std::size_t b)
  : x(a),
    y(b),
    color()
{}


///////////////////////////////////////////////////////////////////////////////
pixel::~pixel()
{}


///////////////////////////////////////////////////////////////////////////////
void 
pixel::print(std::ostream& os) const
{
  os << "pixel[" << (int)x << ',' << (int)y << "](" 
     << color[rgb::r] << ',' 
     << color[rgb::g] << ',' 
     << color[rgb::b] << ')';
}


///////////////////////////////////////////////////////////////////////////////
std::ostream& 
operator<<(std::ostream& os, const pixel& a)
{
  std::ostream::sentry cerberus (os);
  if (cerberus)
    a.print(os);
  return os;
}