#ifndef AMMO_H
#define AMMO_H
#include "collres.h"
#include "grapcollitem.h"
#include "govector.h"
#include "sprite.h"

class BaseAmmo
{
public:
  virtual ~BaseAmmo() = default;
  virtual void act() = 0;
  virtual void move() = 0;
  virtual bool dead() = 0;
};

class Ammo: BaseAmmo
{
public:
  Ammo(double x, double y, double r, double damage, double speed,
       QGraphicsScene* scene, Camera* camera, Sprites* sprites,
       Cord cordTarg, AmmoType type);
  void act() override;
  void move() override;
  bool dead() override;
private:
  bool isDead;
  double x, y, r, damage, speed;
  QGraphicsScene* scene;
  Camera* camera;
  Sprites* sprites;
  Cord targ;
  AmmoType type;

  GrapCollItem* GrItem;
};

#endif // AMMO_H
