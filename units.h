#ifndef UNITS_H
#define UNITS_H
#include "collres.h"

#include "map.h"
#include "sprite.h"
#include "govector.h"
#include "grapcollitem.h"
#include "brain.h"
#include "ammo.h"

class Unit
{
public:
  Unit(UnitDataBuild*, double x ,double y, QGraphicsScene* scene, Camera*, Sprites* sprites, Map* myMap);
  Unit(UnitData*, Camera*,  Sprites* sprites, Map* myMap); //Использовать только при загрузке
  ~Unit();

  Cord* getCord();

  void act();
  void move();
  bool dead();

private:
  void initMove(MoveType type);
  void initArrmor(ArrmorType type);
  void initGun(gunType type, int index, gunSlot gun, Sprites* sprite, Camera* camera, QRectF* rect);
  void initSprite(Camera* camera, Sprites* sprites);
  void initBrain();
  int maxHealth;

  QRectF* rect;
  Brain* brain;

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
  Map* myMap;

  class Move;
  class Arrmor;
  class Gun;

  class Gun
  {
  public:
    virtual ~Gun() = default;
    virtual int getRange() = 0;
    virtual Cord getCord() = 0;
    virtual TargetType getTargType() = 0;
    virtual void attac(void* targ) = 0; // static_cast<>(targ), Во что именно см getTargType
    virtual gunType Type() = 0;
    virtual void updataGr() = 0;
  };

  class Arrmor
  {
  public:
    virtual int getHealthPoints() = 0;
    virtual gunSlots* getSlots() = 0;
    virtual int getAttacPoints() = 0;
    virtual int getLenGun() = 0;
    virtual int getMass() = 0;
    virtual Sprite* getSprite(MoveType, Sprites*) = 0;
    virtual ArrmorType Type() = 0;
  };

  class Move
  {
  public:
    virtual int speed(int /*mass*/) = 0;
    virtual MoveType Type() = 0;
    virtual BaseMoveType getBaseMove() = 0;
    virtual int getHealthPoints() = 0;
  };

  class GunGun: public Gun
  {
  public:
    GunGun(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point);
    int getRange() override;
    Cord getCord() override;
    TargetType getTargType() override;
    void attac(void* targ) override; // static_cast<>(targ), Во что именно см getTargType
    gunType Type() override;
    void updataGr() override;
  private:
    Camera* camera;
    Map* maps;
    Sprites* sprites;
    QGraphicsScene* scene;
    GrapCollItem* GrItem;
    QRectF* rect;
    gunSlot slot;
    int interval;
    double a;
    int point;
  };

  class GunArty: public Gun
  {
  public:
    GunArty(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point);
    int getRange() override;
    Cord getCord() override;
    TargetType getTargType() override;
    void attac(void* targ) override; // static_cast<>(targ), Во что именно см getTargType
    gunType Type() override;
    void updataGr() override;
  private:
    Camera* camera;
    Map* maps;
    Sprites* sprites;
    QGraphicsScene* scene;
    GrapCollItem* GrItem;
    QRectF* rect;
    gunSlot slot;
    int interval;
    double a;
    int point;
  };

  class ArrmorLight: public Arrmor
  {
  public:
    int getHealthPoints() override;
    int getAttacPoints() override;
    int getLenGun() override;
    int getMass() override;
    gunSlots* getSlots() override;
    Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class ArrmorMedium: public Arrmor
  {
    int getHealthPoints() override;
    int getAttacPoints() override;
    int getLenGun() override;
    int getMass() override;
    gunSlots* getSlots() override;
    Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class ArrmorHeavy: public Arrmor
  {
    int getHealthPoints() override;
    int getAttacPoints() override;
    int getLenGun() override;
    int getMass() override;
    gunSlots* getSlots() override;
    Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class MoveWheels: public Move
  {
  public:
    int speed(int /*mass*/);
    MoveType Type();
    BaseMoveType getBaseMove();
    int getHealthPoints();
  };

  class MoveTracks: public Move
  {
  public:
    int speed(int /*mass*/);
    MoveType Type();
    BaseMoveType getBaseMove();
    int getHealthPoints();
  };

  Gun* guns[MaxGun];
  Arrmor* arrmor;
  Move* myMove;
};


#endif // UNITS_H

