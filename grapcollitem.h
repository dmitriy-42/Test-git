#ifndef GRAPCOLLITEM_H
#define GRAPCOLLITEM_H
#include <QGraphicsItem>
#include <QPainter>
#include "camera.h"
#include "sprite.h"
#include <cmath>

enum class TypeObject {Gun, Unit, UnitAir, Block, Ammo, Resource, Building, Stone};



class GrapCollItem: public QGraphicsItem
{
public:
  GrapCollItem(double realX, double realY, double realA, TypeObject type, Sprite* sprite, Camera* camera);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  double getRealR();
  double getRealX();
  double getRealY();
  double getRealA();
  TypeObject getType();
  void setRealPos(double x, double y, double a);
private:
  double realX, realY, realA, realR;
  TypeObject type;
  Sprite* sprite;
  Camera* camera;
};


#endif // GRAPCOLLITEM_H
