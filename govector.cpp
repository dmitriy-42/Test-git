#include "govector.h"


GoVector::GoVector()
{
  clear();
}

GoVector::~GoVector() = default;

void GoVector::addVector(GoVector* vector)
{
  std::cout << "GoVect " << vector->getX() << " " << vector->getY() << "\n";
  addPos(vector->getX(), vector->getY(), vector->getZ());
}

void GoVector::addVector(GoVector vector)
{
  addVector(&vector);
}

void GoVector::addPos(double x, double y, double z)
{
  this->x+=x;
  this->y+=y;
  this->z+=z;
}

void GoVector::addPos(Cord* cord)
{
  this->x = cord->x;
  this->y = cord->y;
}

void GoVector::setSpeed(double speed)
{
  if (ifClear()) return;
  double d = speed/getSpeed();
  x*=d;
  y*=d;
  z*=d;
}

void GoVector::clear()
{
  x = 0;
  y = 0;
  z = 0;
}

double GoVector::getSpeed()
{
  if (ifClear()) return 0;
  return sqrt(x*x+y*y+z*z);
}

double GoVector::getX(){return x;}
double GoVector::getY(){return y;}
double GoVector::getZ(){return z;}

double GoVector::getA()
{
  return atan2(y, x);
}

bool GoVector::ifClear()
{
  return x == 0 and y == 0 and z == 0;
}
