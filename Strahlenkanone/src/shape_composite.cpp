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
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    delete (*i);
  }
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
  bool temp;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    temp = temp || (*i)->intersect(r, rec);
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
  
}