/*
 * File:   loader.cpp
 * Author: riso3860
 *
 * Created on 28. Februar 2010, 16:50
 */

#include <iostream>
#include <fstream>
#include <map>

#include <loader.hpp>

#include <rgb.hpp>
#include <light.hpp>
#include <material.hpp>
#include <shape.hpp>
#include <shape_composite.hpp>

#include <cuboid.hpp>
#include <sphere.hpp>
#include <triangle.hpp>


loader::loader()
{
}

loader::~loader()
{
}

bool
loader::load(char file[], world& w)
{

  std::map<std::string, shape*> shapes;
  std::map<std::string, shape*>::iterator it_shape;
  std::map<std::string, light> lights;
  std::map<std::string, material> materials;
  std::map<std::string, material>::iterator it_mat;


  int i = 0;
  std::ifstream f;
  f.open(file, std::ios::in);

  if (f.good() == 1)
  {
    // Wenn die Datei geoeffnet werden konnte...


    // An den Anfang der Datei springen
    f.seekg(0L, std::ios::beg);

    // in einen string speichern
    std::string string;

    while (!f.eof())
    {
      f >> string;
      // std::cerr << string << std::endl;
      if (string == "define")
      {
        std::cout << "define->";
        f >> string;

        if (string == "material")
        {
          std::string mat_name;
          double ka_r, ka_g, ka_b;
          double kd_r, kd_g, kd_b;
          double ks_r, ks_g, ks_b;
          double m;

          f >> mat_name >> 
                  ka_r >> ka_g >> ka_b >>
                  kd_r >> kd_g >> kd_b >>
                  kd_r >> ks_g >> ks_b >>
                  m;

          rgb ka = rgb(ka_r, ka_g, ka_b);
          rgb kd = rgb(kd_r, kd_g, kd_b);
          rgb ks = rgb(ks_r, ks_g, ks_b);

          material mat = material(ka, kd, ks, m);
          
          materials.insert(std::pair<std::string, material>(mat_name, mat));
          std::cout << "material->" << mat_name << std::endl;

        }

        if (string == "camera")
        {
          std::string cam_name;
          double fov_x;
          f >> cam_name; fov_x;
          std::cout << "camera->" << cam_name << std::endl;

        }

        if (string == "light")
        {
          f >> string;

          /*
           * R G B
           *
           */
          if (string == "diffuse")
          {
            std::string light_name;
            point3d light_pos;
            double la_r, la_g, la_b;
            double ld_r, ld_g, ld_b;

            f >> light_name >>
                    light_pos[0] >> light_pos[1] >> light_pos[2] >> la_r >> la_g >> la_b >> ld_r >> ld_g >> ld_b;

            rgb la = rgb(la_r, la_g, la_b);
            rgb ld = rgb(ld_r, ld_g, ld_b);
          }
          if (string == "ambient")
          {
            std::string light_name;
            double la_r, la_g, la_b;
            double ld_r, ld_g, ld_b;

            f >> light_name >> la_r >> la_g >> la_b >> ld_r >> ld_g >> ld_b;

            rgb la = rgb(la_r, la_g, la_b);
            rgb ld = rgb(ld_r, ld_g, ld_b);
          }
        }

        if (string == "shape")
        {

          std::cout << "shape->";
          f >> string;

          if (string == "box")
          {
            std::string name;
            point3d p1;
            point3d p2;
            std::string mat_name;

            f >> name >> p1[0] >> p1[1] >> p1[2] >> mat_name;

            it_mat = materials.find(mat_name);

                  
            cuboid *c = new cuboid(p1, p2, (*it_mat).second);

            shapes.insert(std::pair<std::string, shape*>(name, c));

            std::cout << "box->" << name << std::endl;


      
          }

          if (string == "sphere")
          {
            std::string name;
            point3d center;
            double radius;
            std::string mat_name;

            f >> name >> center[0] >> center[1] >> center[2] >> radius >> mat_name;

            it_mat = materials.find(mat_name);


            sphere *s = new sphere(center, radius, (*it_mat).second);

            shapes.insert(std::pair<std::string, shape*>(name, s));

            std::cout << "sphere->" << name << std::endl;

          }

          if (string == "triangle")
          {
            std::string name;
            point3d p1;
            point3d p2;
            point3d p3;
            std::string mat_name;

            f >> name >> p1[0] >> p1[1] >> p1[2] >> p2[0] >> p2[1] >> p2[2] >> p3[0] >> p3[1] >> p3[2] >> mat_name;

            it_mat = materials.find(mat_name);

            triangle *t = new triangle(p1, p2, p3, (*it_mat).second);

            shapes.insert(std::pair<std::string, shape*>(name, t));

            std::cout << "triangle->" << name << std::endl;

          }

          if (string == "composite")
          {
            std::string name;
            std::string child;
            std::vector<std::string> children;

            f >> name;

            std::string line;
            while (std::getline(f, line))
            {
              std::cout << "boo" << std::endl;
              f >> child;
              children.push_back(child);
            }

            shape_composite *sc = new shape_composite;

            std::cout << "composite->" << name << "->";

            for(std::vector<std::string>::iterator i = children.begin(); i != children.end(); std::advance(i ,1))
            {
              it_shape = shapes.find(*i);

              std::cout << (*it_shape).first;

              sc->add((*it_shape).second);
            }

            shapes.insert(std::pair<std::string, shape*>(name, sc));

            std::cout << std::endl;



          }
        }
        if (string == "transform")
        {
         
         f >> string;

         if (string == "translate")
         {
            vector3d offset;
            f >> offset[0] >> offset[1] >> offset[2];
          }

         if (string == "rotate")
         {
           double angle;
           vector3d v;
           f >> angle >> v[0] >> v[1] >> v[2];

         }
         if (string == "scale")
         {
           double value;
           f >> value;
         }

      }

      if (string == "render")
      {
         std::cout << "render" << std::endl;
         std::string cam_name;
         std::string filename;
         int x_res;
         int y_res;

         f >> cam_name >> filename >> x_res >> y_res;

      }
    }

   }
    
    return 1;
  }
  // Wenn die Datei nicht geoeffnet werden konnte,
  std::cerr << "Datei konnte nicht geoeffnet werden" << std::endl;
  return 0;

}
