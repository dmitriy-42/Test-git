#include "grapcollitem.h"

GrapCollItem::GrapCollItem(double realX, double realY, double realA, TypeObject type, Sprite* sprite, Camera* camera)
    :realX(realX), realY(realY), realA(realA), type(type), sprite(sprite), camera(camera)
{
  int z;
  switch (type)
  {
    case TypeObject::UnitAir:    z = 5; break;
    case TypeObject::Ammo:       z = 4; break;
    case TypeObject::Gun:        z = 3; break;
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
  return QRectF(realX - camera->getX(), realY - camera->getY(), sprite->w / camera->getH(), sprite->h / camera->getH());
}

void GrapCollItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  setRotation(realA - camera->getA());
  painter->drawImage(boundingRect(), sprite->tex);
}

double GrapCollItem::getRealX(){return realX;}
double GrapCollItem::getRealY(){return realY;}
double GrapCollItem::getRealA(){return realA;}
TypeObject GrapCollItem::getType(){return type;}


void GrapCollItem::setRealPos(double x, double y, double a)
{
  realX = x;
  realY = y;
  realA = a;
}
