/** file: test-srpingmass.cpp
 ** brief: Tests the spring mass simulation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

int main(int argc, char** argv)
{

  const double mass = 0.05 ;
  const double radius = 0.02 ;
  const double naturalLength = 0.95 ;
  const double stiffness = 1;// decide a random value
  const double damping=0.1;

  Mass m1(Vector2(-.5,0), Vector2(0,0), mass, radius) ;
  Mass m2(Vector2(+.5,0), Vector2(0,0), mass, radius) ;

  Spring spring(&m1,&m2, naturalLength, stiffness, damping);
  //here it does not include damping since it is assigned a value 0/01 in header file.

  SpringMass springmass(&spring) ;

  //simulation
  const double dt = 1.0/30 ;
  for (int i = 0 ; i < 100 ; ++i) {
    springmass.step(dt) ;
    springmass.display() ;
  }

  return 0 ;
}
