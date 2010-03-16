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

  // Globals

  // Der Loader lädt alle Shapes in diese Map und generiert daraus ein Master-Shape Composite
  std::map<std::string, shape*> shapes;
  std::map<std::string, shape*>::iterator it_shape;

  // In der Material-Map werde alle Materials gespeichert um diese per map.find() einem Shape zuordnen zu können
  std::map<std::string, material> materials;
  std::map<std::string, material>::iterator it_mat;

  // Ein std::vector für Lichter - keine Pointer
  std::vector<light> lights;

  // Das Master-Shape Composite was im Loader gefüllt wird.
  shape_composite *sc = new shape_composite;

  // Die Hintergrundfarbe
  rgb background=rgb(0.0, 0.0, 0.0);

  // Der Ambiente Beleuchtungskoeffzient
  // Wird aus der Summe der Ambienten Lichtquellen berechnet
  rgb la=rgb(0.0, 0.0, 0.0);

  // Camera-Öffnungswinkel - Standardmässig 45°
  double fov_x = 45.0;

  // Der Dateiname unter dem das Bild gespeichert wird
  std::string filename = "image.ppm";
  
  // Auslösung
  int x_res = 500;
  int y_res = 500;


  // Wir legen einen File-Stream f auf die übergebene Datei f an
  std::ifstream f;
  f.open(file, std::ios::in);

  if (f.good() == 1)
  {
    // Wenn die Datei geoeffnet werden konnte...
    // An den Anfang der Datei springen
    f.seekg(0L, std::ios::beg);

    // Wird false wenn Datei zu Ende ist oder andere Probleme auftreten
    while (f)
    {
      std::string string;
      std::string line;

      // Die Datei wird zeilenweise Eingelesen.
      // Es wird ein inputstream (iss) auf die Zeile gelegt.

      std::getline(f, line);
      std::istringstream iss(line);


      // Hier beginnt der eigentliche Loader
      iss >> string;

      // Shapes, Material, Licht werden hier geladen.

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
          bool mirror;

          iss >> mat_name >>
                  ka_r >> ka_g >> ka_b >>
                  kd_r >> kd_g >> kd_b >>
                  ks_r >> ks_g >> ks_b >>
                  m >> mirror;

          rgb ka=rgb(ka_r, ka_g, ka_b);
          rgb kd=rgb(kd_r, kd_g, kd_b);
          rgb ks=rgb(ks_r, ks_g, ks_b);

          material mat=material(ka, kd, ks, m, mirror);

          // Jedes Material kommt in den Temporären Material-Container

          materials.insert(std::pair<std::string, material> (mat_name, mat));
          std::cout << "material->" << mat_name << std::endl;
          // std::cout << "material.size() :" << materials.size() << std::endl;

        }


        // Nur diffuse Lichter kommen in den Licht-Vektor
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

            // Wir prüfen ob es das material gibt
            if (it_mat != materials.end())
            { 
              cuboid *c=new cuboid(p1, p2, (*it_mat).second);
              shapes.insert(std::pair<std::string, shape*>(name, c));
              std::cout << "box->" << name << std::endl;
            }
            
          }


          if (string == "sphere")
          {
            std::string name;
            point3d center;
            double radius;
            std::string mat_name;

            iss >> name >> center[0] >> center[1] >> center[2] >> radius >> mat_name;

            it_mat=materials.find(mat_name);
            
            if (it_mat != materials.end())
            {
              
              sphere *s=new sphere(center, radius, (*it_mat).second);
              shapes.insert(std::pair<std::string, shape*>(name, s));
              std::cout << "sphere->" << name << std::endl;
            }
            else std::cerr << "Material für Sphere (" << name << " nicht gefunden. Fehler in SDF-Datei" << std::endl;

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

            if (it_mat != materials.end())
            {
               triangle *t = new triangle(p1, p2, p3, (*it_mat).second);
               shapes.insert(std::pair<std::string, shape*>(name, t));
               std::cout << "triangle->" << name << " mat: " << mat_name << std::endl;
            }
            else std::cerr << "Material für Triangle (" << name << " nicht gefunden. Fehler in SDF-Datei" << std::endl;

          }


          if (string == "composite")
          {
            std::string name;
            std::string child;
            std::vector<std::string> children;

            // Wir legen uns ein Temporäres Composite an
            shape_composite *sc_tmp = new shape_composite;


            iss >> name;

            std::cout << "composite->" << name;

            // Alle Blätter des jeweiligen Composites werden im vector childen gespeichert
             while (iss >> child) {
              children.push_back(child);
            }



            // In der Shape-Map wird nach dem Namen des Blattes gesucht und dieses ggf. in den Shape-Container eingefügt.
            for (std::vector<std::string>::iterator i=children.begin(); i != children.end(); std::advance(i, 1))
            {

              std::cout << "->" << (*i);
              it_shape=shapes.find(*i);

              if (it_shape != shapes.end() )
              {
                sc_tmp->add((*it_shape).second);
                std::cout << "WTF?" << sc_tmp->size();
              }
              else std::cerr << "Composite" << name << ": Shape " << (*i) << " konnte nicht im Shape-Container gefunden werden" << std::endl;

              
            }

            // Mehrere Composites

            // heißt das Composite "root" wird es dem Shape-Container hinzugefügt
            if (name == "root")
            {
              std::cout << "\n root composite detected: adding to shape" << std::endl;
              // Der Temporäre Shape-Container der mit den Children des Composites gefüllt ist..
              // ersetzt den Normalen Shape Container. d.h. ist in einer SDF-Datei ein composite
              // vorhanden und shapes die nicht darin vorkommen so werden diese Verworfen
              //sc = sc_tmp;
              shapes.insert(std::pair<std::string, shape*>(name, sc_tmp));
            }
            else
            {
              // Für den Fall das es mehrere Composites gibt werden diese einfach an das Root-Composite angehangen
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


      // Transformation

      if (string == "transform")
      {

        std::cout << "transform->";
        std::string name;
        iss >> name;

        std::cout << name << "->";

        it_shape=shapes.find(name);
        std::cout << "\n name des shapes das transformiert wird: " << it_shape->first << std::endl;

        iss >> string;
        
        if (string == "translate")
        {
          vector3d offset;
          iss >> offset[0] >> offset[1] >> offset[2];

         it_shape->second->translate(offset[0], offset[1], offset[2]);
          std::cout << "\n translate auf " << (*it_shape).first << std::endl;
          
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
        if (string == "rotatex")
        {
          double angle;
          iss >> angle;

          if (it_shape != shapes.end())
          {
            it_shape->second->rotatex(angle);
            std::cout << "rotatex" << std::endl;
          }


        }
        if (string == "rotatey")
        {
          double angle;
          iss >> angle;

          if (it_shape != shapes.end())
          {
            it_shape->second->rotatey(angle);
            std::cout << "rotatey" << std::endl;
          }


        }
        if (string == "rotatez")
        {
          double angle;
          iss >> angle;

          if (it_shape != shapes.end())
          {
            it_shape->second->rotatez(angle);
            std::cout << "rotatez" << std::endl;
          }


        }

        if (string == "scale")
        {
          double x;
          double y;
          double z;

          iss >> x >> y >> z;

          if (it_shape != shapes.end())
          {
            it_shape->second->scale(x, y, z);
            std::cout << "scale" << std::endl;
          }


          
        }

      }

       
    



      // Camera



      if (string == "camera")
      {
        std::string cam_name;
        iss >> cam_name >> fov_x;
        std::cout << "camera->" << cam_name << "->" << fov_x << std::endl;
      }
      

      // Render

      // we gracefully ignore cam_name because we only have 1 camera

      if (string == "render")
      {

        std::string cam_name;

        // Folgende Variablen sind am Beginn der Datei deklariert worden:
        //std::string filename;
        //int x_res;
        //int y_res;

        iss >> cam_name >> filename >> x_res >> y_res;
        std::cout << "render->" << cam_name << "->" << filename << std::endl;

      }

    }

    // Nachdem die Datei fertig eingelesen wurde...
    // bauen wir uns unser Master-Composite, das der render()-Funktion der world-Klasse übergeben wird
    shape_composite *master = new shape_composite;

    // Gibt es ein composite mit namen "root" Fügen wir nur das Composite Hinzu
    // Gibt es KEIN composite werden alle Shapes im Container hinzugefügt
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


  bool result=w.init(fov_x, filename, x_res, y_res, *master, lights, la, background);

  return result;
  }

  // Wenn die Datei nicht geoeffnet werden konnte,
  std::cerr << "Datei konnte nicht geoeffnet werden" << std::endl;
  return 0;
  

 


}
