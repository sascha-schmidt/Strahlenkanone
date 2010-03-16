#include "shape_composite.hpp"
#include <cassert>
#include <vector>
#include <utility>
#include <iostream>

shape_composite::shape_composite()
: data_(), shape()
{
}

shape_composite::~shape_composite()
{
  /*composite wird erst mit Programmende destruiert->
    alles im Stack und freestore wird eh gelöscht*/
}

void
shape_composite::add(shape* s)
{
  assert(s != 0);
  data_.push_back(s);
  bbox();
}

bool 
shape_composite::intersect(ray r, shade &rec) const
{
  bool temp = false;
  //if(bboxintersect(r))
  {
    for(std::vector<shape*>::const_iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
    {
      bool akt = (*i)->intersect(r, rec);
      temp = (temp || akt);
    }
  }
  return temp;
}

bool
shape_composite::rotate(double a, double x, double y, double z)
{
    std::cout << "shape_composite::rotate" << std::endl;
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
      std::cout << "shape_composite::rotate für element im container" << std::endl;
    bool akt = (*i)->rotate(a, x, y, z);
    temp = temp && akt;
  }
  bbox();
  return temp;
}

bool
shape_composite::rotatex(double angle)
{
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    bool akt = (*i)->rotatex(angle);
    temp = temp && akt;
  }
  bbox();
  return temp;
}

bool
shape_composite::rotatey(double angle)
{
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    bool akt = (*i)->rotatey(angle);
    temp = temp && akt;
  }
  bbox();
  return temp;
}

bool
shape_composite::rotatez(double angle)
{
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    bool akt = (*i)->rotatez(angle);
    temp = temp && akt;
  }
  bbox();
  return temp;
}

bool
shape_composite::scale(double x, double y, double z)
{
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); std::advance(i ,1))
  {
    bool akt = (*i)->scale(x,y,z);
    temp = temp && akt;
  }
  bbox();
  return temp;
}

bool
shape_composite::translate(double x, double y, double z)
{
  std::cout << "shape_composite::translate" << std::endl;
  bool temp = true;
  for(std::vector<shape*>::iterator i = data_.begin(); i != data_.end(); ++i)
  {
   
    bool akt = (*i)->translate(x,y,z);
    temp = temp && akt;
  }
  bbox();
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

unsigned
shape_composite::size() const
{
  return data_.size();
}