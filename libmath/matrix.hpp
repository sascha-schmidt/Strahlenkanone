/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2009 Bauhaus University Weimar                                                   */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  matrix.hpp                                                                      */
/*  project    :  lectures in programming && software engineering, winter 09/10                   */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/
#ifndef BUW_MATRIX_HPP
#define BUW_MATRIX_HPP

// includes, system
#include <iosfwd> // fwd. decl: std::ostream

// includes, project
#include <vector3d.hpp>


// forward declarations
class point3d;
  
class matrix 
{
public : // c'tors / d'tor
  
  matrix            ( );
  matrix            ( matrix const& );
  matrix            ( double const [16] );

  ~matrix           ( );
  
public : // methods

  void              swap          ( matrix& rhs );
  matrix&           operator=     ( matrix const& rhs );

  double const&     operator()    ( unsigned row, unsigned col ) const;
  double&           operator()    ( unsigned row, unsigned col );

  double const&     operator[]    ( unsigned ) const;
  double&           operator[]    ( unsigned );
  
  matrix&           operator*=    ( matrix const& );

  double            determinant   ( ) const;

  bool              invert        ( );
  void              transpose     ( );

  bool              is_invertible ( ) const; // det(M) != 0

public : // static methods

  static matrix const& null();     // m[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
  static matrix const& identity(); // m[[1,0,0,0],[0,1,0,0],[0,0,1,0],[0,0,0,1]]
  
private:

  double data_[16];
};

// extern operators
matrix         operator*        ( matrix const&, matrix const&  );
matrix         operator*        ( matrix const&, double         );
matrix         operator*        ( double,        matrix const&  );
matrix         operator/        ( matrix const&, double         );

point3d        operator*        ( matrix const&, point3d const& );
vector3d       operator*        ( matrix const&, vector3d const&);

// caution! floating point errors may cause inequality
bool           operator==       ( matrix const&, matrix const&  );
bool           operator!=       ( matrix const&, matrix const&  );

std::ostream&  operator<<       ( std::ostream&, matrix const&  );

// external functions
matrix         make_translation ( double, double, double );
matrix         make_translation ( vector3d const& );

matrix         make_scale       ( double, double, double );
matrix         make_scale       ( vector3d const& );

matrix         make_rotation_x  ( double );
matrix         make_rotation_y  ( double );
matrix         make_rotation_z  ( double );
matrix         make_rotation  ( double a, double x, double y, double z);
matrix         make_rotation  ( double a, vector3d v);

double         determinant      ( matrix const& );
matrix         inverse          ( matrix const& );
matrix         transpose        ( matrix const& );

bool           is_invertible    ( matrix const& );


#endif // BUW_MATRIX_HPP
