/* 
 * File:   eSDF-Loader.hpp
 * Author: sascha
 *
 * Created on 28. Februar 2010, 15:58
 */

#ifndef _ESDF_LOADER_HPP
#define	_ESDF_LOADER_HPP

#include <world.hpp>

//Loader für eSDF Dateien
class loader
{
public:

    loader();

    ~loader();
  //Lädt die in file übergebene Datei und initialisiert damit die world
  bool load(char file[], world& w);
  void tokenize(const std::string, std::vector<std::string>&, const std::string&);
};

#endif	/* _ESDF_LOADER_HPP */

