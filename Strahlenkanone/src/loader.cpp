/*
 * File:   loader.cpp
 * Author: riso3860
 *
 * Created on 28. Februar 2010, 16:50
 */

#include <iostream>
#include <fstream>
#include <sstream> 
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

  std::map<std::string, material> materials;
  std::map<std::string, material>::iterator it_mat;

  std::vector<light> lights;

  shape_composite *sc = new shape_composite;

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
    while (f)
    {
      std::string string;
      std::string line;
      std::getline(f, line);
      std::istringstream iss(line);
      
      iss >> string;
      // std::cerr << string << std::endl;
      if (string == "define")
      {
        std::cout << "define->";
        iss >> string;

        if (string == "material")
        {
          std::string mat_name;
          double ka_r, ka_g, ka_b;
          double kd_r, kd_g, kd_b;
          double ks_r, ks_g, ks_b;
          double m;

          iss >> mat_name >>
                  ka_r >> ka_g >> ka_b >>
                  kd_r >> kd_g >> kd_b >>
                  ks_r >> ks_g >> ks_b >>
                  m;

          rgb ka=rgb(ka_r, ka_g, ka_b);
          rgb kd=rgb(kd_r, kd_g, kd_b);
          rgb ks=rgb(ks_r, ks_g, ks_b);

          material mat=material(ka, kd, ks, m);

          materials.insert(std::pair<std::string, material> (mat_name, mat));
          std::cout << "material->" << mat_name << std::endl;
          std::cout << "material.size() :" << materials.size() << std::endl;

        }



        if (string == "light")
        {
          iss >> string;
          std::cout << "light->";

          if (string == "diffuse")
          {
            std::string light_name;
            point3d light_pos;
            double ld_r, ld_g, ld_b;

            iss >> light_name >>
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

            iss >> light_name >> la_r >> la_g >> la_b;
            la+=rgb(la_r, la_g, la_b);

            std::cout << "ambient->" << light_name << std::endl;

          }
        }

        if (string == "shape")
        {

          std::cout << "shape->";
          iss >> string;

          if (string == "box")
          {
            std::string name;
            point3d p1;
            point3d p2;
            std::string mat_name;

            iss >> name >> p1[0] >> p1[1] >> p1[2] >> p2[0] >> p2[1] >> p2[2] >> mat_name;

            it_mat=materials.find(mat_name);


            cuboid *c=new cuboid(p1, p2, (*it_mat).second);

            //material stuff (rgb (0.5,0.5,0.5), rgb (0.5,0.5,0.5), rgb (0.5,0.5,0.5), 2);
            //cuboid *c=new cuboid(p1, p2, );
            shapes.insert(std::pair<std::string, shape*>(name, c));

            std::cout << "box->" << name << std::endl;

          }


          if (string == "sphere")
          {
            std::string name;
            point3d center;
            double radius;
            std::string mat_name;

            iss >> name >> center[0] >> center[1] >> center[2] >> radius >> mat_name;

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

            iss >> name >> p1[0] >> p1[1] >> p1[2] >> p2[0] >> p2[1] >> p2[2] >> p3[0] >> p3[1] >> p3[2] >> mat_name;

            it_mat=materials.find(mat_name);

            triangle *t = new triangle(p1, p2, p3, (*it_mat).second);

            shapes.insert(std::pair<std::string, shape*>(name, t));

            std::cout << "triangle->" << name << " mat: " << mat_name << std::endl;

          }

          if (string == "composite")
          {
            std::string name;
            std::string child;
            std::vector<std::string> children;

            shape_composite *sc_tmp = new shape_composite;


            iss >> name;

            std::cout << "composite->" << name;

             while (iss >> child) {
              children.push_back(child);
            }



            for (std::vector<std::string>::iterator i=children.begin(); i != children.end(); std::advance(i, 1))
            {

              std::cout << "->" << (*i);
              it_shape=shapes.find(*i);

              sc_tmp->add((*it_shape).second);

              
            }

            // TODO mehrere composites

            if (name == "root")
            {
              std::cout << "\n root composite detected: adding to shape" << std::endl;
              sc = sc_tmp;
              shapes.insert(std::pair<std::string, shape*>(name, sc));
            }
            else
            {
              if ( shapes.find("root") != shapes.end() )
              {
                std::cout << "\n non-root composite detected: adding to root-composite" << std::endl;
                sc->add(sc_tmp);
              }
            }

            std::cout << std::endl;

          }

        }

      }

<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
<<<<<<< HEAD:Strahlenkanone/src/loader.cpp

  
=======
>>>>>>> 043b363f925a2ee5af49dda7121a92e9fc98c599:Strahlenkanone/src/loader.cpp
=======
>>>>>>> 21318891c4d81286af9ca853a4fbbe79952c83fd:Strahlenkanone/src/loader.cpp
      if (string == "transform")
      {

        std::cout << "transform->";
        std::string name;
        iss >> name;

        std::cout << name << "->";
        it_shape=shapes.find(name);

        iss >> string;
        if (string == "translate")
        {
          vector3d offset;
          iss >> offset[0] >> offset[1] >> offset[2];

          if (it_shape != shapes.end())
          {
            it_shape->second->translate(offset[0], offset[1], offset[2]);
            std::cout << "translate" << std::endl;
          }
        }

        if (string == "rotate")
        {
          double angle;
          vector3d v;
          iss >> angle >> v[0] >> v[1] >> v[2];

          if (it_shape != shapes.end())
          {
            it_shape->second->rotate(angle, v[0], v[1], v[2]);
            std::cout << "rotate" << std::endl;
          }

          
        }
        if (string == "scale")
        {
          double x;
          double y;
          double z;

          iss >> x >> y >> z;

<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
          (*it_shape).second->scale(x, y, z);
=======
=======
>>>>>>> 21318891c4d81286af9ca853a4fbbe79952c83fd:Strahlenkanone/src/loader.cpp
          if (it_shape != shapes.end())
          {
            it_shape->second->scale(x, y, z);
            std::cout << "scale" << std::endl;
          }
<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
>>>>>>> 043b363f925a2ee5af49dda7121a92e9fc98c599:Strahlenkanone/src/loader.cpp
=======
>>>>>>> 21318891c4d81286af9ca853a4fbbe79952c83fd:Strahlenkanone/src/loader.cpp

          
        }

      }
<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
       
    
=======
=======
>>>>>>> 21318891c4d81286af9ca853a4fbbe79952c83fd:Strahlenkanone/src/loader.cpp
        

      
>>>>>>> 043b363f925a2ee5af49dda7121a92e9fc98c599:Strahlenkanone/src/loader.cpp
      if (string == "camera")
      {
        std::string cam_name;
        iss >> cam_name >> fov_x;
        std::cout << "camera->" << cam_name << "->" << fov_x << std::endl;
      }
      

      if (string == "render")
      {

        std::string cam_name;
        std::string filename;
        int x_res;
        int y_res;

        iss >> cam_name >> filename >> x_res >> y_res;
        std::cout << "render->" << cam_name << "->" << filename << std::endl;

      }

    }

  }
  

  shape_composite *master = new shape_composite;

  std::map<std::string, shape*>::iterator master_iter = shapes.find("root");

  if ( master_iter != shapes.end() )
  {
    std::cout << "adding root composite" << std::endl;
    master->add((*master_iter).second);
    std::cout << "size of root-composite: " << sc->size() << std::endl;
  }
  else
  {
    std::cout << "no composite found - adding shapes to master composite" << std::endl;
    for (std::map<std::string, shape*>::iterator i = shapes.begin(); i != shapes.end(); std::advance(i, 1))
    {
      master->add((*i).second);
    }

    
  }



<<<<<<< HEAD:Strahlenkanone/src/loader.cpp
  bool result=w.init(fov_x, *master, lights, background, la);
=======
  bool result=w.init(fov_x, *master, lights, la, background);
>>>>>>> 21318891c4d81286af9ca853a4fbbe79952c83fd:Strahlenkanone/src/loader.cpp
  return result;
  // Wenn die Datei nicht geoeffnet werden konnte,
  //std::cerr << "Datei konnte nicht geoeffnet werden" << std::endl;
  //return 0;

}
