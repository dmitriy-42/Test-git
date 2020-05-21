#ifndef GOVECTOR_H
#define GOVECTOR_H
#include "collres.h"

class GoVector
{
public:
  GoVector();
  ~GoVector();
  void addVector(GoVector* vector);
  void addVector(GoVector vector);
  void addPos(double x, double y, double z);
  void addPos(Cord* cord);
  void setSpeed(double speed);
  void clear();
  double getSpeed();
  double getX();
  double getY();
  double getZ();
  double getA();
private:
  double x,y,z;
  bool ifClear();
};

#endif // GOVECTOR_H
