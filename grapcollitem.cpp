#include "grapcollitem.h"

GrapCollItem::GrapCollItem(double realX, double realY, double realA, TypeObject type, Sprite* sprite, Camera* camera, Brain* brain, void* shell)
    :realX(realX), realY(realY), realA(realA), realR(sqrt(sprite->h*sprite->h+sprite->w*sprite->w)/2), type(type), sprite(sprite), camera(camera), brain(brain), shell(shell)
{
  damage = 0.0;
  int z;
  switch (type)
  {
    case TypeObject::UnitAir:    z = 5; break;
    case TypeObject::Ammo:       z = 4; break;
    case TypeObject::Gun:        z = 10; break;
    case TypeObject::Unit:
    case TypeObject::Resource:
    case TypeObject::Building:
    case TypeObject::Stone:      z = 2; break;
    case TypeObject::Block:      z = 1; break;
    default:                     z = 0;
  }
  setZValue(z);
}

QRectF GrapCollItem::boundingRect() const
{
  double h = camera->getH();
  return QRectF((realX - camera->getX())/h, (realY - camera->getY())/h,
                (sprite->w) / h, (sprite->h) / h);
}

void GrapCollItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  setRotation(realA - camera->getA());
  painter->drawImage(boundingRect(), *(sprite->tex));
}

void GrapCollItem::addDamage(double dam)
{
  damage += dam;
}

double GrapCollItem::getDamage()
{
  double k = damage;
  damage = 0;
  return k;
}

double GrapCollItem::getRealR(){return realR;}
double GrapCollItem::getRealX(){return realX;}
double GrapCollItem::getRealY(){return realY;}
double GrapCollItem::getRealA(){return realA;}
TypeObject GrapCollItem::getType(){return type;}

TypeGrap GrapCollItem::getTypeGrap() {return TypeGrap::GrapCollItem;}


void GrapCollItem::setRealPos(double x, double y, double a)
{
  realX = x;
  realY = y;
  realA = a;
}



Detected::Detected(double realX, double realY, double realA, double realW, double realH, Camera* camera)
  :realX(realX), realY(realY), realA(realA), realW(realW), realH(realH), camera(camera)
{
  //pass
}

Detected::Detected(double realX, double realY, double realR, Camera *camera)
  :realX(realX), realY(realY), realA(0), realW(realR*2), realH(realR*2), camera(camera)
{
  //pass
}

QRectF Detected::boundingRect() const
{
  double h = camera->getH();
  return QRectF((realX - camera->getX())/h, (realY - camera->getY())/h,
                (realW) / h, (realH) / h);
}

void Detected::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
  //pass
}

TypeGrap Detected::getTypeGrap() {return TypeGrap::Detect;}

void Detected::setRealPos(double x, double y)
{
  realX = x;
  realY = y;
}

Kostul::Kostul(Map *map)
{
  myMap = map;
}

void Kostul::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
  myMap->start();
}

QRectF Kostul::boundingRect() const
{
  return QRectF(20,20,20,20);
}

TypeGrap Kostul::getTypeGrap()
{
  return TypeGrap::Kastul;
}


