#ifndef UNITS_H
#define UNITS_H
#include "map.h"
#include "sprite.h"
#include "govector.h"
#include "grapcollitem.h"
#include <iostream>

const int MaxGun = 10;
enum gunType{Gun, Minigun, Arty};
enum ArrmorType{Light, Medium, Heavy, Over};
enum MoveType{Wheels, Tracks, Plane, Jet};
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
  //Unit(ArrmorType, MoveType);
  Unit();
  ~Unit();

  int getSlotLen();
  void init(double x, double y, gunType[MaxGun]);

  void act();
  void move();
  void dead();

private:
  double x;
  double y;
  double a;
  double r;
  bool isColl(GrapCollItem*);
  bool isCollLand(GrapCollItem*);
  bool isCollAir(GrapCollItem*);
  double health;
  GrapCollItem* GrItem;
  QGraphicsScene* scene;
  GoVector* moveVect;

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
    virtual MoveType Type() = 0;
  };

  Gun* guns[MaxGun];
  Arrmor* arrmor;
  Move* myMove;
};


#endif // UNITS_H

