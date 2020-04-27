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

bool Unit::isColl(GrapCollItem * Item)
{
  switch (myMove->Type())
  {
    case MoveType::Jet:
    case MoveType::Plane: return isCollAir(Item);
    case MoveType::Tracks:
    case MoveType::Wheels: return isCollLand(Item);
    default:
      std::cerr << "isColl default\n";
      return false;
  }
}

bool Unit::isCollLand(GrapCollItem * Item)
{
  switch (Item->getType())
  {
    case TypeObject::Unit:
    case TypeObject::Stone:
    case TypeObject::Resource:
    case TypeObject::Building: return true;
    default: return false;
  }
}

bool Unit::isCollAir(GrapCollItem * Item)
{
  switch (Item->getType())
  {
    case TypeObject::UnitAir: return true;
    default: return false;
  }
}
