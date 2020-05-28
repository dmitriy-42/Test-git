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
  Unit(UnitData* data, QGraphicsScene* scene, Camera *camera, Sprites* sprites, Map* myMap); //Использовать только при загрузке
  ~Unit();

  Cord* getCord();

  void act();
  void move();
  bool dead();

  unsigned long long getUserId();

private:
  unsigned long long id;
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
  double* a = new double;
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
    Gun(QRectF* rect, GrapCollItem* GrItem, gunSlot slot, double* unitA);
    virtual ~Gun() = default;
    virtual int getRange() = 0;
    Cord AtoXY(double x, double y, double a);
    Cord getCord();
    virtual TargetType getTargType() = 0;
    virtual void attac(void* targ) = 0; // static_cast<>(targ), Во что именно см getTargType
    virtual gunType Type() = 0;
    void updataGr();
  protected:
    double test = 0;
    double* unitA;
    gunSlot slot;
    int interval;
    double a;
    GrapCollItem* GrItem;
    QRectF* rect;
    double h;
    double w;
  };

  class Arrmor
  {
  public:
    virtual int getHealthPoints() = 0;
    virtual gunSlots* getSlots() = 0;
    virtual int getAttacPoints() = 0;
    virtual int getLenGun() = 0;
    virtual int getMass() = 0;
    virtual const Sprite* getSprite(MoveType, Sprites*) = 0;
    virtual ArrmorType Type() = 0;
  };

  class Move
  {
  public:
    virtual double speed(int /*mass*/) = 0;
    virtual MoveType Type() = 0;
    virtual BaseMoveType getBaseMove() = 0;
    virtual int getHealthPoints() = 0;
  };

  class GunGun: public Gun
  {
  public:
    GunGun(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point, double* unitA);
    int getRange() override;
    TargetType getTargType() override;
    void attac(void* targ) override; // static_cast<>(targ), Во что именно см getTargType
    gunType Type() override;
  private:
    Camera* camera;
    Map* maps;
    Sprites* sprites;
    QGraphicsScene* scene;
    QRectF* rect;
    int point;
  };

  class GunArty: public Gun
  {
  public:
    GunArty(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point, double* unitA);
    int getRange() override;
    TargetType getTargType() override;
    void attac(void* targ) override; // static_cast<>(targ), Во что именно см getTargType
    gunType Type() override;
  private:
    Camera* camera;
    Map* maps;
    Sprites* sprites;
    QGraphicsScene* scene;
    QRectF* rect;
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
    const Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class ArrmorMedium: public Arrmor
  {
    int getHealthPoints() override;
    int getAttacPoints() override;
    int getLenGun() override;
    int getMass() override;
    gunSlots* getSlots() override;
    const Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class ArrmorHeavy: public Arrmor
  {
    int getHealthPoints() override;
    int getAttacPoints() override;
    int getLenGun() override;
    int getMass() override;
    gunSlots* getSlots() override;
    const Sprite* getSprite(MoveType move, Sprites* sprites) override;
    ArrmorType Type() override;
  };

  class MoveWheels: public Move
  {
  public:
    double speed(int /*mass*/);
    MoveType Type();
    BaseMoveType getBaseMove();
    int getHealthPoints();
  };

  class MoveTracks: public Move
  {
  public:
    double speed(int /*mass*/);
    MoveType Type();
    BaseMoveType getBaseMove();
    int getHealthPoints();
  };

  Gun* guns[MaxGun];
  Arrmor* arrmor;
  Move* myMove;
};


#endif // UNITS_H

