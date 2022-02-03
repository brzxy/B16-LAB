/** file: test-springmass-graphics.cpp
 ** brief: Tests the spring mass simulation with graphics
 ** author: Andrea Vedaldi
 **/

#include "graphics.h"
#include "springmass.h"

#include <iostream>
#include <sstream>
#include <iomanip>

/* ---------------------------------------------------------------- */
class SpringMassDrawable : public SpringMass, public Drawable
/* ---------------------------------------------------------------- */
{
private:
  Figure figure ;

public:
  SpringMassDrawable(Spring *spring)
  : figure("Springmass"),SpringMass(spring)
  {
    figure.addDrawable(this) ;
  }
  //need to draw two masses and one spring
  void draw() {
    Mass * m1 = spring->getMass1() ; 
    Mass * m2 = spring->getMass2() ;

    Vector2 m1position = m1->getPosition() ;
    Vector2 m2position = m2->getPosition() ;

    //first draw mass1
    figure.drawCircle(m1position.x,m1position.y,m1->getRadius()) ;
    //first draw mass2
    figure.drawCircle(m2position.x,m2position.y,m2->getRadius()) ;
    //draw the spring
    double thickness=1;//define thickness to draw the line
    figure.drawLine(m1position.x,m1position.y,m2position.x,m2position.y,thickness);
  }

  void display() {
    figure.update() ;
  }
} ;



int main(int argc, char** argv)
{
  glutInit(&argc,argv) ;
  const double dt = 1/60.0 ;
  const double mass = 0.05 ;
  const double radius = 0.1 ;
  const double naturalLength = 0.5 ;
  const double stiffness = 0.1;// decide a random value
  const double damping=0.01;

  Mass m1(Vector2(-.5,0), Vector2(0,0), mass, radius) ;
  Mass m2(Vector2(+.5,0), Vector2(0,0), mass, radius) ;

  Spring spring(&m1,&m2, naturalLength, stiffness, damping);
  //here it does not include damping since it is assigned a value 0.01 in header file.

  SpringMassDrawable springmass(&spring);

  run(&springmass, dt) ;
  return 0;
}
