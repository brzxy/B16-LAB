/** file: ball.h
 ** brief: Ball class
 ** author: Andrea Vedaldi
 **/

#ifndef __ball__
#define __ball__

#include "simulation.h"

class Ball : public Simulation
{
public:
  // Constructors and member functions
  Ball(double _x = 0, double _y = 0, double _vx = 0.3, double _vy = -0.1) ;
  void step(double dt) ;
  void display() ;

  //define Getter and Setter
  double GetX() const;
  double GetY() const;
  void SetX(double _x);
  void SetY(double _y);

protected:
  // Data members
  // Position and velocity of the ball
  double x ;
  double y ;
  double vx ;
  double vy ;

  // Mass and size of the ball
  double m ;
  double r ;

  // Gravity acceleration
  double g ;

  // Geometry of the box containing the ball
  double xmin ;
  double xmax ;
  double ymin ;
  double ymax ;
} ;

#endif /* defined(__ball__) */
