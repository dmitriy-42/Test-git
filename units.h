#ifndef UNITS_H
#define UNITS_H
#include "map.h"

const int MaxGun = 10;
enum gunType{};
enum ArrmorType{};
enum MoveType{};
struct gunSlot
{
  double x, y;
  double a, b;
};

struct gunSlots
{
  int len;
  gunSlot slot[MaxGun];
};




class Unit
{
public:
  Unit();
  ~Unit();
  void act();
  double x;
  double y;
private:
  class Gun
  {
  public:
    virtual int getRange() = 0;
    virtual bool attac(Unit*) = 0;
    virtual void act() = 0;
  };

  class Arrmor
  {
  public:
    virtual int getHealthPoints() = 0;
    virtual gunSlots getSlots() = 0;
    virtual double getAttacPoints() = 0;
  };

  class Move
  {
  public:
    virtual int speed() = 0;
  };

  Gun* guns[MaxGun];
  Arrmor* arrmor;
  Move* move;
};


#endif // UNITS_H

