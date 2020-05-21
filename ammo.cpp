#include "ammo.h"

/*
 *     /  / x \2    \
 * y = | -|---| + 1 | * d
 *     \  \ r /     /
 *
 * x - расстояние до цели
 * y - урон который получит цель
 * r - радиус взрыва
 * d - урон взрыва
 *
 * Формула даёт отрицательные значения для целей не поподающих в радиус поражения
 * Надо проверять из за особеностей Detected (большая часть будет в радиусе)
*/




Ammo::Ammo(double x, double y, double r, double damage, double speed, QGraphicsScene* scene, Camera* camera, Sprites* sprites, Cord cordTarg, AmmoType type)
  :isDead(false) ,x(x), y(y), r(r), damage(damage), speed(speed), scene(scene), camera(camera), sprites(sprites), targ(cordTarg), type(type)
{
  GrItem = new GrapCollItem(x,y,0,TypeObject::Ammo, sprites->get(spBAmmo), camera, nullptr, this);
}

void Ammo::act()
{
  //pass
}

void Ammo::move()
{
  GoVector vect;
  vect.addPos(&targ);
  if (vect.getSpeed() > speed) vect.setSpeed(speed);
  x = vect.getX();
  y = vect.getY();
}

bool Ammo::dead()
{
  if (x == targ.x and y == targ.y)
  {
    isDead = true;
  }
  else
  {
    QList <QGraphicsItem *> collList;
    int i = 0;
    GrapCollItem* j;

    switch (type)
    {
    case AmmoType::Def:
      collList = scene->collidingItems(GrItem);
      for (i = 0; i < collList.size();i++)
      {
        if (static_cast<Grap*>(collList[i])->getTypeGrap() == TypeGrap::GrapCollItem)
        {
          j = static_cast<GrapCollItem*>(collList[i]);
          switch (j->getType())
          {
          case TypeObject::Building:
          case TypeObject::Stone:
          case TypeObject::Resource: isDead = true;
          default: break;
          }
        }
      }
    default: break;
    }
  }
  if (isDead)
  {
    Detected detect(x,y,r,camera);
    scene->addItem(&detect);

    QList <QGraphicsItem *> collList = scene->collidingItems(&detect);
    for (int i = 0; i < collList.size();i++)
    {
      if (static_cast<Grap*>(collList[i])->getTypeGrap() == TypeGrap::GrapCollItem)
      {
        GrapCollItem* j = static_cast<GrapCollItem*>(collList[i]);
        double xj = j->getRealX() - x;
        double yj = j->getRealY() - y;
        double d = (-((xj*xj + yj*yj)/(r*r))+1)*damage;
        if (d > 0) j->addDamage(d);
      }
    }

    scene->removeItem(&detect);
  }

  return isDead;
}
