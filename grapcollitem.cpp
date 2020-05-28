#include "grapcollitem.h"

GrapCollItem::GrapCollItem(double realX, double realY, double realA, TypeObject type, const Sprite* sprite, Camera* camera, Brain* brain, void* shell)
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

  Cord cord2 = AtoXY(-(sprite->w/2.0), -(sprite->h/2.0), realA);
  //if (realA != 0.0) std::cout << "w and h and a " << sprite->w << " " << sprite->h << " " << realA <<  "\n" << sprite << "\n\n";
  Cord cord = AtoXY(realX + cord2.x, realY + cord2.y, -realA);

  /*
  Cord cord;
  cord.x = realX;
  cord.y = realY;
  */
  /*
  if (type != TypeObject::Block)
    std::cout << (cord.x - camera->getX())/h << " " << (cord.y - camera->getY())/h << "\n";
    */

  return QRectF((cord.x - camera->getX())/h, (cord.y - camera->getY())/h,
                (sprite->w) / h, (sprite->h) / h);
}

void GrapCollItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  setRotation(realA - camera->getA());
  //setRotation(0);
  painter->drawImage(boundingRect(), *(sprite->tex));
  bool t;
  switch (type) {
    case TypeObject::Unit:
    case TypeObject::UnitAir:
    case TypeObject::Building: t = true; break;
    default: t = false;
    }
  if (t and foc)
    {
      QRectF rect = boundingRect();
      rect.setX(rect.x() - 20);
      rect.setY(rect.y() - 20);
      rect.setWidth(rect.width() + 20);
      rect.setHeight(rect.height() + 20);
      painter->drawImage(rect, *(sprite->foc));
    }
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

Brain *GrapCollItem::getBrain()
{
  return brain;
}

double GrapCollItem::getRealR(){return realR;}
double GrapCollItem::getRealX(){return realX;}
double GrapCollItem::getRealY(){return realY;}
double GrapCollItem::getRealA(){return realA;}

double GrapCollItem::getRealH()
{
  return sprite->h;
}

double GrapCollItem::getRealW()
{
  return sprite->w;
}

unsigned long long GrapCollItem::getId()
{
  return sprite->id;
}

void GrapCollItem::setFoc(bool foc)
{
  this->foc = foc;
}

bool GrapCollItem::getFoc()
{
  return foc;
}

TypeObject GrapCollItem::getType(){return type;}

TypeGrap GrapCollItem::getTypeGrap() {return TypeGrap::GrapCollItem;}


void GrapCollItem::setRealPos(double x, double y, double a)
{
  realX = x;
  realY = y;
  realA = a;
}

Cord GrapCollItem::AtoXY(double x, double y, double a) const
{
  Cord cord;
  double q = (a/180)*PI;
  double q2 = (a+90)/180*PI;

  cord.x = x*cos(q)+y*cos(q2);
  cord.y = x*sin(q)+y*sin(q2);

  return cord;
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


Icon::Icon(int x, int y, int size, const Sprite *sprite)
  :x(x), y(y), size(size) , sprite(sprite)
{
  setZValue(10000);
}

QRectF Icon::boundingRect() const
{
  return QRectF(x,y,size,size);
}

void Icon::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  painter->drawImage(boundingRect(), *(sprite->tex));
}

TypeGrap Icon::getTypeGrap()
{
  return TypeGrap::Icon;
}

DetectedP::DetectedP(int x, int y, const Sprite* sprite)
  :x(x), y(y), w(10), h(10), sprite(sprite)
{}

QRectF DetectedP::boundingRect() const
{
  int x1, y1, w1, h1;
  if (x > w){x1 = w; w1 = x;}
  else {x1 = x; w1 = w;};
  if (y > h){y1 = h; h1 = y;}
  else {y1 = y; h1 = h;};
  return QRectF(x1,y1,w1,h1);
}

void DetectedP::paint(QPainter* /*painter*/, const QStyleOptionGraphicsItem*, QWidget*)
{
  //painter->drawImage(boundingRect(), *(sprite->tex));
}

void DetectedP::setPos(int w, int h)
{
  this->w = w;
  this->h = h;
}

void DetectedP::setPos2(int x, int y)
{
  this->x = x;
  this->y = y;
}

TypeGrap DetectedP::getTypeGrap()
{
  return TypeGrap::Detect;
}
