#include "shape_composite.hpp"
#include <cassert>
#include <vector>
#include <utility>

shape_composite::shape_composite()
: data_(), shape()
{
}

shape_composite::~shape_composite()
{
  //for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  //{
  //  delete (*i);
  //}
  //composite selber liegt im Stack und ist damit weg
}

void
shape_composite::add(shape* s)
{
  assert(s != 0);
  data_.push_back(s);
}

bool 
shape_composite::intersect(ray& r, shade &rec)
{
  bool temp = false;
  if(bboxintersect(r))
  {
    for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
    {
      temp = temp || (*i)->intersect(r, rec);
    }
  }
  return temp;
}

bool
shape_composite::rotate(double a, double x, double y, double z)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->rotate(a, x, y, z);
  }
  return temp;
}

bool
shape_composite::rotatex(double angle)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->rotatex(angle);
  }
  return temp;
}

bool
shape_composite::rotatey(double angle)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->rotatey(angle);
  }
  return temp;
}

bool
shape_composite::rotatez(double angle)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->rotatez(angle);
  }
  return temp;
}

bool
shape_composite::scale(double x, double y, double z)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->scale(x,y,z);
  }
  return temp;
}

bool
shape_composite::translate(double x, double y, double z)
{
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp && (*i)->translate(x,y,z);
  }
  return temp;
}

void
shape_composite::bbox()
{
  ppp temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    ppp akt = (*i)->getbbox();
    temp.first[0] = std::min(temp.first[0], akt.first[0]);
    temp.first[1] = std::min(temp.first[1], akt.first[1]);
    temp.first[2] = std::min(temp.first[2], akt.first[2]);
    temp.second[0] = std::max(temp.second[0], akt.second[0]);
    temp.second[1] = std::max(temp.second[1], akt.second[1]);
    temp.second[2] = std::max(temp.second[2], akt.second[2]);
  }
  setbbox(temp);
}