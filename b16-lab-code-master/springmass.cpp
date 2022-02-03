/** file: springmass.cpp
 ** brief: SpringMass simulation implementation
 ** author: Andrea Vedaldi
 **/

#include "springmass.h"

#include <iostream>

/* ---------------------------------------------------------------- */
// class Mass
/* ---------------------------------------------------------------- */

Mass::Mass()
: position(), velocity(), force(), mass(1), radius(1)
{ }

Mass::Mass(Vector2 position, Vector2 velocity, double mass, double radius)
: position(position), velocity(velocity), force(), mass(mass), radius(radius),
xmin(-1),xmax(1),ymin(-1),ymax(1)
{ }

void Mass::setForce(Vector2 f)
{
  force = f ;
}

void Mass::addForce(Vector2 f)
{
  force = force + f ;
}

Vector2 Mass::getForce() const
{
  return force ;
}

Vector2 Mass::getPosition() const
{
  return position ;
}

Vector2 Mass::getVelocity() const
{
  return velocity ;
}

double Mass::getRadius() const
{
  return radius ;
}

double Mass::getMass() const
{
  return mass ;
}

double Mass::getEnergy(double gravity) const
{
  //enery is two parts: potential and kinetic

  //potential
  double potential_energy = mass * gravity * position.y ;

  //kinetic
  double kinetic_energy = 0.5 * mass * velocity.norm2();

  //total
  double total_energy = potential_energy + kinetic_energy;

  return total_energy;
}

void Mass::step(double dt)
{
  Vector2 final_position = position + velocity * dt + 0.5 * force / mass * dt * dt; 
  Vector2 final_velocity = velocity + force / mass * dt; 
  
  //x direction
  if (xmin + radius <= final_position.x && final_position.x <= xmax - radius) {
    position.x = final_position.x ;
    velocity.x = final_velocity.x ;
  } else {
    velocity.x = -velocity.x ;
  }

  //y direction 
  if (ymin + radius <= final_position.y && final_position.y <= ymax - radius) {
    position.y = final_position.y ;
    velocity.y = final_velocity.y ;
  } else {
    velocity.y = -velocity.y ;
  }

}

/* ---------------------------------------------------------------- */
// class Spring
/* ---------------------------------------------------------------- */

Spring::Spring(Mass * mass1, Mass * mass2, double naturalLength, double stiffness, double damping)
: mass1(mass1), mass2(mass2),
naturalLength(naturalLength), stiffness(stiffness), damping(damping)
{ }

Mass * Spring::getMass1() const
{
  return mass1 ;
}

Mass * Spring::getMass2() const
{
  return mass2 ;
}

Vector2 Spring::getForce() const
{

    Vector2 x1 = mass1->getPosition();
    Vector2 x2 = mass2->getPosition();
    Vector2 v1 = mass1->getVelocity();
    Vector2 v2 = mass2->getVelocity();
    
    double length = getLength() ;

    Vector2 u12 = (1/length)*(x2-x1) ;
    Vector2 v12 = dot((v2-v1),u12)*u12;

    Vector2 F1 = stiffness * (length - naturalLength) * u12;
    Vector2 F2 = damping * v12;
    Vector2 F = F1 + F2;
  return F ;
}

double Spring::getLength() const
{
  Vector2 u = mass2->getPosition() - mass1->getPosition() ;
  return u.norm() ;
}

double Spring::getEnergy() const {
  double length = getLength() ;
  double dl = length - naturalLength;
  return 0.5 * stiffness * dl * dl ;
}

std::ostream& operator << (std::ostream& os, const Mass& m)
{
  os<<"("
  <<m.getPosition().x<<","
  <<m.getPosition().y<<")" ;
  return os ;
}

std::ostream& operator << (std::ostream& os, const Spring& s)
{
  return os<<"$"<<s.getLength() ;
}

/* ---------------------------------------------------------------- */
// class SpringMass : public Simulation
/* ---------------------------------------------------------------- */

SpringMass::SpringMass(Spring *s, double gravity)
: spring(s), gravity(gravity)
{ }
//loading a spring and gravity in SpringMass
void SpringMass::display()
{
  Mass * m1 = spring->getMass1() ; 
  Mass * m2 = spring->getMass2() ;

  Vector2 m1position = m1->getPosition() ;
  Vector2 m2position = m2->getPosition() ;
  std::cout<< m1position.x <<" "<<m1position.y<<" "
  <<m2position.x<<" "<<m2position.y<<std::endl ;

}

double SpringMass::getEnergy() const
{
  double energy = 0 ;
  /* INCOMPLETE: TYPE YOUR CODE HERE */
  return energy;
}

void SpringMass::step(double dt)
{
  Vector2 g(0,-gravity);
  //Get mass of m1 and m2
  Mass * m1 = spring->getMass1() ; 
  Mass * m2 = spring->getMass2() ;
  
  //Set initial force to be gravity
  m1->setForce(g*(m1->getMass())) ; 
  m2->setForce(g*(m2->getMass())) ; 

  //Accumulate the forces
  Vector2 F = spring->getForce() ; 
  m1->addForce(F) ;
  m2->addForce(-1*F) ;

  //update the state on mass 1&2
  m1->step(dt);
  m2->step(dt);
}


/* INCOMPLETE: TYPE YOUR CODE HERE */


