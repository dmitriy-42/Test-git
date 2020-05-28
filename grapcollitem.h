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
  GrapCollItem(double realX, double realY, double realA, TypeObject type, const Sprite* sprite, Camera* camera, Brain* brain, void* shell);
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
  double getRealH();
  double getRealW();

  unsigned long long getId();

  void setFoc(bool foc);
  bool getFoc();

  Cord AtoXY(double x, double y, double a) const;

  TypeObject getType();
  TypeGrap getTypeGrap() override;
  void setRealPos(double x, double y, double a);
private:
  bool foc = false;

  double damage;

  double realX, realY, realA, realR;
  TypeObject type;
  const Sprite* sprite;
  Camera* camera;
  Brain* brain;

  void* shell;
};

class Icon: public Grap
{
public:
  Icon(int x, int y, int size, const Sprite* sprite);
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  TypeGrap getTypeGrap() override;
private:
  int x, y, size;
  const Sprite* sprite;
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

class DetectedP: public Grap
{
public:
  DetectedP(int x, int y, const Sprite* sprite);

  QRectF boundingRect() const override;
  void paint(QPainter*, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  void setPos(int w, int h);
  void setPos2(int x, int y);
  TypeGrap getTypeGrap() override;
private:
  int x, y, w, h;
  const Sprite* sprite;
};

class Kostul: public Grap // Map не хочет работать с таймером а времени сделать как надо нет
{
public:
  Kostul(Map* map);
  void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget *) override;
  QRectF boundingRect() const override;
  TypeGrap getTypeGrap() override;
  Map* myMap;
};


#endif // GRAPCOLLITEM_H
