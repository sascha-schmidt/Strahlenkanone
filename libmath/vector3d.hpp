/* 
 * File:   vector3d.hpp
 * Author: sascha
 *
 * Created on 27. Oktober 2009, 15:56
 */

#ifndef _vector3d_HPP
#define	_vector3d_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream

class point3d;

class vector3d
{
public:
    //c'tors
    vector3d();
    vector3d(double x, double y, double z);
    vector3d(point3d const& eins, point3d const& zwei);

    //d'tor
    ~vector3d();


    //Indexoperatoren
    double& operator [](unsigned index);
    double const& operator[](unsigned index) const;

    //Länge
    double length() const;  //verändert nichts am Obj.

    //normalisieren
    void normalize();

    //Rechenoperationen
    vector3d& operator+=(vector3d const& rhs);
    vector3d& operator-=(vector3d const& rhs);
    vector3d& operator*=(double skalar);

private:
    double data_[4];  //3+1 für homogene Koordinaten
};

double dot(vector3d const& lhs, vector3d const& rhs);
double dot(point3d const& lhs, vector3d const& rhs);
double dot(vector3d const& lhs, point3d const& rhs);

//kreuz
vector3d cross(vector3d const& lhs, vector3d const& rhs);
//Pseudo eigentliche Berechnung zw. Vektor Ursprung->Punkt und dem anderen Vektor:
vector3d cross(point3d const& lhs, vector3d const& rhs);
vector3d cross(point3d const& lhs, point3d const& rhs);

//externe Operatoren
vector3d operator+(vector3d const& lhs, vector3d const& rhs);
vector3d operator-(vector3d const& lhs, vector3d const& rhs);
vector3d operator*(double lhs, vector3d const& rhs);
vector3d operator*(vector3d const& lhs, double rhs);

std::ostream& operator<<( std::ostream&, vector3d const&  );


#endif	/* _vector3d_HPP */

