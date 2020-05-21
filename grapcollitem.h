#ifndef GRAPCOLLITEM_H
#define GRAPCOLLITEM_H
#include "collres.h"

#include "camera.h"
#include "sprite.h"



#include "map.h" // Нужен для кастыля


class Grap: public QGraphicsItem
{
public:
  virtual TypeGrap getTypeGrap() = 0;
};


class GrapCollItem: public Grap // Нужен всем кого надо рисовать
{
public:
  GrapCollItem(double realX, double realY, double realA, TypeObject type, Sprite* sprite, Camera* camera, Brain* brain, void* shell);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void addDamage(double);
  double getDamage();

  Brain* getBrain();
  void* getMyShell();
  double getRealR();
  double getRealX();
  double getRealY();
  double getRealA();
  TypeObject getType();
  TypeGrap getTypeGrap() override;
  void setRealPos(double x, double y, double a);
private:
  double damage;

  double realX, realY, realA, realR;
  TypeObject type;
  Sprite* sprite;
  Camera* camera;
  Brain* brain;

  void* shell;
};

class Detected: public Grap // Нужен для обнаружения других объектов в определёном месте. (Обноруживает по GrapCollItem)
{
public:
  Detected(double realX, double realY, double realA, double realW, double realH, Camera* camera);
  Detected(double realX, double realY, double realR, Camera* camera);
  QRectF boundingRect() const override;
  void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget *) override;

  TypeGrap getTypeGrap() override;
  void setRealPos(double x, double y);
private:
  double realX, realY, realA, realW, realH;
  Camera* camera;
};

class Kostul: public Grap // Map не хочет работать с таймером а верени сделать как надо нет
{
public:
  Kostul(Map* map);
  void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget *) override;
  QRectF boundingRect() const override;
  TypeGrap getTypeGrap() override;
  Map* myMap;
};


#endif // GRAPCOLLITEM_H
