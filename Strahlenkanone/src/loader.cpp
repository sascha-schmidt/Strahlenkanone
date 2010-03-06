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

void
loader::tokenize(const std::string str, std::vector<std::string>& tokens, const std::string& delimiters=" ")
{
  // Skip delimiters at beginning.
  std::string::size_type lastPos=str.find_first_not_of(delimiters, 0);
  // Find first "non-delimiter".
  std::string::size_type pos=str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // Found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
    // Skip delimiters.  Note the "not_of"
    lastPos=str.find_first_not_of(delimiters, pos);
    // Find next "non-delimiter"
    pos=str.find_first_of(delimiters, lastPos);

  }
}

bool
loader::load(char file[], world& w)
{

  std::map<std::string, shape*> shapes;
  std::map<std::string, shape*>::iterator it_shape;
  std::map<std::string, material> materials;
  std::map<std::string, material>::iterator it_mat;

  shape_composite sc;

  std::vector<light> lights;

  rgb background=rgb(0.0, 0.0, 0.0);

  rgb la=rgb(0.0, 0.0, 0.0);

  double fov_x = 45.0;


  int i=0;
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

          rgb ka=rgb(ka_r, ka_g, ka_b);
          rgb kd=rgb(kd_r, kd_g, kd_b);
          rgb ks=rgb(ks_r, ks_g, ks_b);

          material mat=material(ka, kd, ks, m);

          materials.insert(std::pair<std::string, material > (mat_name, mat));
          std::cout << "material->" << mat_name << std::endl;

        }



        if (string == "light")
        {
          f >> string;
          std::cout << "light->";

          /*
           * R G B
           *
           */
          if (string == "diffuse")
          {

            std::string light_name;
            point3d light_pos;
            double ld_r, ld_g, ld_b;

            f >> light_name >>
                    light_pos[0] >> light_pos[1] >> light_pos[2] >> ld_r >> ld_g >> ld_b;


            rgb ld=rgb(ld_r, ld_g, ld_b);

            light l=light(light_pos, ld);
            lights.push_back(l);

            std::cout << "diffuse->" << light_name << std::endl;
          }

          if (string == "ambient")
          {
            std::string light_name;
            double la_r, la_g, la_b;

            f >> light_name >> la_r >> la_g >> la_b;
            la+=rgb(la_r, la_g, la_b);

            std::cout << "ambient->" << light_name << std::endl;

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

            it_mat=materials.find(mat_name);


            cuboid *c=new cuboid(p1, p2, (*it_mat).second);

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

            it_mat=materials.find(mat_name);


            sphere *s=new sphere(center, radius, (*it_mat).second);

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

            it_mat=materials.find(mat_name);

            triangle *t=new triangle(p1, p2, p3, (*it_mat).second);

            shapes.insert(std::pair<std::string, shape*>(name, t));

            std::cout << "triangle->" << name << std::endl;

          }

          if (string == "composite")
          {
            std::string name;
            std::string child;
            std::vector<std::string> children;

            f >> name;

            std::cout << "composite->" << name;


            std::string line;
            std::getline(f, line);

            tokenize(line, children, " ");




            for (std::vector<std::string>::iterator i=children.begin(); i != children.end(); std::advance(i, 1))
            {

              std::cout << "->" << (*i);
              it_shape=shapes.find(*i);
              sc.add((*it_shape).second);
            }

            // TODO mehrere composites

            //shapes.insert(std::pair<std::string, shape*>(name, sc));

            std::cout << std::endl;

          }

        }

      }


     /* if (string == "transform")
      {

        std::cout << "transform->";
        std::string name;
        f >> name;

        std::cout << name << "->";
        it_shape=shapes.find(name);

        f >> string;

        if (string == "translate")
        {
          vector3d offset;
          f >> offset[0] >> offset[1] >> offset[2];

          it_shape->second->translate(offset[0], offset[1], offset[2]);
          std::cout << "translate" << std::endl;
        }

        if (string == "rotate")
        {
          double angle;
          vector3d v;
          f >> angle >> v[0] >> v[1] >> v[2];

          it_shape->second->rotate(angle, v[0], v[1], v[2]);

          std::cout << "rotate" << std::endl;
        }
        if (string == "scale")
        {
          double x;
          double y;
          double z;

          f >> x >> y >> z;

          it_shape->second->scale(x, y, z);

          std::cout << "scale" << std::endl;
        }

      }

      */

      /*
      if (string == "camera")
      {
        std::string cam_name;
        f >> cam_name >> fov_x;
        std::cout << "camera->" << cam_name << "->" << fov_x << std::endl;
      }
       *
       */

      if (string == "render")
      {

        std::string cam_name;
        std::string filename;
        int x_res;
        int y_res;

        f >> cam_name >> filename >> x_res >> y_res;
        std::cout << "render->" << cam_name << "->" << filename << std::endl;

      }

      else
      {
          std::string empty;
          std::getline(f, empty);
      }



    }

  }
  bool result=w.init(fov_x, sc, lights, background, la);
  return result;
  // Wenn die Datei nicht geoeffnet werden konnte,
  //std::cerr << "Datei konnte nicht geoeffnet werden" << std::endl;
  //return 0;

}
