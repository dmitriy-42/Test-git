#include "units.h"


Unit::Unit()
{

}

Unit::~Unit()
{

}

void Unit::act()
{
  QList <QGraphicsItem *> collList = scene->collidingItems(GrItem);
  for (int i = 0; i < collList.size();i++)
  {
    GrapCollItem* j = static_cast<GrapCollItem*>(collList[i]);
    if (isColl(j))
    {
      GoVector vect;
      vect.addPos(j->getRealX(),j->getRealY(),0);
      vect.setSpeed(
            -((-(vect.getSpeed()/(r))+1) * r *2)
            );
      moveVect->addVector(vect);
    }
  }
}

void Unit::move()
{
  x += moveVect->getX();
  y += moveVect->getY();
  GrItem->setRealPos(x, y, a);
  moveVect->clear();
}

void Unit::dead()
{
  if (health <= 0) delete this;
}
