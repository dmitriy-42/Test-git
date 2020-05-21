#include "units.h"


Unit::Unit(UnitDataBuild* data, double x ,double y, QGraphicsScene* scene, Camera* camera,  Sprites* sprites, Map* myMap)
  :x(x), y(y), scene(scene), myMap(myMap)
{
  rect = new QRectF;
  rect->setX(x);
  rect->setY(y);

  moveVect = new GoVector;

  a = 0;

  initMove(data->move);
  initArrmor(data->arrmor);
  gunSlots* guns = arrmor->getSlots();
  for (int i = 0; i < guns->len;i++)
  {
    initGun(data->guns[i], i, guns->slot[i], sprites, camera, rect);
  }
  initBrain();
  initSprite(camera, sprites);

  maxHealth = 30 + 20 * (arrmor->getHealthPoints()+myMove->getHealthPoints());
  health = maxHealth;

  delete guns;
}

Unit::Unit(UnitData* data, Camera *camera,  Sprites* sprites, Map* myMap)
  :myMap(myMap)
{
  rect = new QRectF;
  rect->setX(x);
  rect->setY(y);

  moveVect = new GoVector;

  x = data->x;
  y = data->y;
  a = data->a;
  health = data->health;

  initMove(data->move);
  initArrmor(data->arrmor);
  gunSlots* guns = arrmor->getSlots();
  for (int i = 0; i < guns->len;i++)
  {
    initGun(data->guns[i], i, guns->slot[i], sprites, camera, rect);
  }
  initBrain();
  initSprite(camera, sprites);

  maxHealth = 30 + 20 * (arrmor->getHealthPoints()+myMove->getHealthPoints());

  delete guns;
  delete data;
}

Unit::~Unit()
{
  scene->removeItem(GrItem);
  delete GrItem;
  for (int i = 0; i < arrmor->getLenGun(); i++)
  {
    delete guns[i];
  }
  //Здесь утечка памяти, на днях исправлю.
}

Cord *Unit::getCord()
{
  Cord* cord = new Cord;
  cord->x = x;
  cord->y = y;
  return cord;
}

void Unit::act()
{
  brain->Move();

  moveVect->addVector(brain->Move());
  moveVect->setSpeed(myMove->speed(arrmor->getMass()));
  a = moveVect->getA();

  QList <QGraphicsItem *> collList = scene->collidingItems(GrItem);
  for (int i = 0; i < collList.size();i++)
  {
    if (static_cast<Grap*>(collList[i])->getTypeGrap() == TypeGrap::GrapCollItem)
    {
      GrapCollItem* j = static_cast<GrapCollItem*>(collList[i]);
      if (isColl(j))
      {
        GoVector vect;
        vect.addPos(x- j->getRealX(),y- j->getRealY(),0);
        vect.setSpeed(vect.getSpeed()/2.0);
        moveVect->addVector(vect);
      }
    }
  }

  for (int i = 0; i < arrmor->getLenGun(); i++)
  {
    void* targ = nullptr;
    Cord cord = guns[i]->getCord();
    double r = guns[i]->getRange();
    switch (guns[i]->getTargType())
    {
    case TargetType::Cord: targ = brain->attack(cord, r); break;
    case TargetType::Unit: targ = brain->attackUnit(cord, r); break;
    default:
        std::cerr << "getTargType\n";
    }
    guns[i]->attac(targ); //gun удаляет targ (он знает тип)
  }
}

void Unit::move()
{

  x += moveVect->getX();
  y += moveVect->getY();
  rect->setX(x);
  rect->setY(y);
  GrItem->setRealPos(x, y, a);
  moveVect->clear();

}

bool Unit::dead()
{
  health -= GrItem->getDamage();
  bool isdead = false;
  switch (myMove->getBaseMove())
  {
  case BaseMoveType::Air: break;
  case BaseMoveType::Land: isdead = myMap->get(x,y) == nullptr; break;
  case BaseMoveType::None: std::cerr << "Unit have BaseMove None!!!";
  }
  return isdead or health <= 0;
}

void Unit::initMove(MoveType type)
{
  switch (type)
  {
  case MoveType::Wheels: myMove = new MoveWheels; break;
  case MoveType::Tracks: myMove = new MoveTracks; break;
  default:
      myMove = new MoveWheels;
  }
}

void Unit::initArrmor(ArrmorType type)
{
  switch (type)
  {
  case ArrmorType::Light: arrmor = new ArrmorLight; break;
  case ArrmorType::Medium: arrmor = new ArrmorMedium; break;
  case ArrmorType::Heavy: arrmor = new ArrmorHeavy; break;
  default:
      arrmor = new ArrmorLight;
    }
}

void Unit::initGun(gunType type, int index, gunSlot gun, Sprites* sprite, Camera* camera, QRectF* rect)
{
  Gun* g;
  switch (type)
  {
  case gunType::Gun: g = new GunGun(gun, sprite, camera, rect, scene,myMap, arrmor->getAttacPoints()); break;
  case gunType::Arty: g = new GunArty(gun, sprite, camera, rect, scene,myMap, arrmor->getAttacPoints()); break;
  default: g = new GunGun(gun, sprite, camera, rect, scene,myMap, arrmor->getAttacPoints());
  }
  guns[index] = g;
}

void Unit::initSprite(Camera* camera, Sprites* sprites)
{
  TypeObject type;
  if (myMove->getBaseMove() == BaseMoveType::Land) type = TypeObject::Unit;
  else type = TypeObject::UnitAir;
  GrItem = new GrapCollItem(x,y,a,type,arrmor->getSprite(myMove->Type(), sprites),camera, brain, this);
  scene->addItem(GrItem);
}

void Unit::initBrain()
{
  std::vector <HaveGun> * vect = new std::vector <HaveGun>;
  rect = new QRectF;
  rect->setX(x);
  rect->setY(y);
  brain = new Brain(vect, nullptr, myMove->getBaseMove(), rect, 1, 0);
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
    case TypeObject::Building:
      return true;
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

int Unit::ArrmorLight::getHealthPoints()
{
  return 1;
}

int Unit::ArrmorLight::getAttacPoints()
{
  return 1;
}

int Unit::ArrmorLight::getLenGun()
{
  return 1;
}

int Unit::ArrmorLight::getMass()
{
  return 0;
}

gunSlots* Unit::ArrmorLight::getSlots()
{
  gunSlot gun;
  gun.x = 0;
  gun.y = 0;
  gunSlots* guns = new gunSlots;
  guns->len = 1;
  guns->slot[0] = gun;
  return guns;
}

Sprite *Unit::ArrmorLight::getSprite(MoveType move, Sprites* sprites)
{
  return sprites->get(spMap + (int)Type()*spMove + (int)move);
}

ArrmorType Unit::ArrmorLight::Type()
{
  return ArrmorType::Light;
}

int Unit::ArrmorMedium::getHealthPoints()
{
  return 3;
}

int Unit::ArrmorMedium::getAttacPoints()
{
  return 2;
}

int Unit::ArrmorMedium::getLenGun()
{
  return 1;
}

int Unit::ArrmorMedium::getMass()
{
  return 20;
}

gunSlots* Unit::ArrmorMedium::getSlots()
{
  gunSlot gun;
  gun.x = 0;
  gun.y = 0;
  gunSlots* guns = new gunSlots;
  guns->len = 1;
  guns->slot[0] = gun;
  return guns;
}

Sprite *Unit::ArrmorMedium::getSprite(MoveType move, Sprites* sprites)
{
  return sprites->get(spMap + (int)Type()*spMove + (int)move);
}

ArrmorType Unit::ArrmorMedium::Type()
{
  return ArrmorType::Medium;
}

int Unit::ArrmorHeavy::getHealthPoints()
{
  return 5;
}

int Unit::ArrmorHeavy::getAttacPoints()
{
  return 4;
}

int Unit::ArrmorHeavy::getLenGun()
{
  return 1;
}

int Unit::ArrmorHeavy::getMass()
{
  return 30;
}

gunSlots* Unit::ArrmorHeavy::getSlots()
{
  gunSlot gun;
  gun.x = 0;
  gun.y = 0;
  gunSlots* guns = new gunSlots;
  guns->len = 1;
  guns->slot[0] = gun;
  return guns;
}

Sprite *Unit::ArrmorHeavy::getSprite(MoveType move, Sprites* sprites)
{
  return sprites->get(spBArrmorAndMove + (int)Type()*spMove + (int)move);
}

ArrmorType Unit::ArrmorHeavy::Type()
{
  return ArrmorType::Heavy;
}

int Unit::MoveWheels::speed(int mass)
{
  return 0.1 * (1 - mass / 100);
}

MoveType Unit::MoveWheels::Type()
{
  return MoveType::Wheels;
}

BaseMoveType Unit::MoveWheels::getBaseMove()
{
  return BaseMoveType::Land;
}

int Unit::MoveWheels::getHealthPoints()
{
  return 0;
}


int Unit::MoveTracks::speed(int mass)
{
  return 0.07 * (1 - mass / 100);
}

MoveType Unit::MoveTracks::Type()
{
  return MoveType::Tracks;
}

BaseMoveType Unit::MoveTracks::getBaseMove()
{
  return BaseMoveType::Land;
}

int Unit::MoveTracks::getHealthPoints()
{
  return 1;
}

Unit::GunGun::GunGun(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point)
  :camera(camera), maps(maps), sprites(sprites), scene(scene), rect(rect), slot(slot), interval(0), point(point)
{
  interval = 0;
  Cord cord = getCord();
  GrItem = new GrapCollItem(cord.x, cord.y, a, TypeObject::Gun, sprites->get(spBGun + (int)Type()), camera, nullptr, this);
  scene->addItem(GrItem);
}

int Unit::GunGun::getRange()
{
  return 10.0;
}

Cord Unit::GunGun::getCord()
{
  //to do
  Cord cord;
  cord.x = rect->x();
  cord.y = rect->y();
  return cord;
}

TargetType Unit::GunGun::getTargType()
{
  return TargetType::Cord;
}

void Unit::GunGun::attac(void *targ)
{
  if (interval) interval--;
  if (targ != nullptr)
  {
    Cord* cordTarg = static_cast<Cord*>(targ);
    GoVector vect;
    vect.addPos(cordTarg);
    a = vect.getA();
    if (interval == 0)
    {
      Cord cord = getCord();
      Ammo* ammo = new Ammo(cord.x, cord.y, 2.0, 15+point*10, 0.2, scene, camera, sprites, *cordTarg, AmmoType::Def);
      maps->addAmmo((BaseAmmo*)ammo);
      interval = 5;
    }
    delete cordTarg;
  }
}

gunType Unit::GunGun::Type()
{
  return gunType::Gun;
}

void Unit::GunGun::updataGr()
{
  Cord cord = getCord();
  GrItem->setRealPos(cord.x,cord.y, a);
  if (interval > 0) interval--;
}



Unit::GunArty::GunArty(gunSlot slot, Sprites* sprites, Camera* camera, QRectF* rect, QGraphicsScene* scene, Map* maps, int point)
  :camera(camera), maps(maps), sprites(sprites), scene(scene), rect(rect), slot(slot), interval(0), point(point)
{
  interval = 0;
  Cord cord = getCord();
  GrItem = new GrapCollItem(cord.x, cord.y, a, TypeObject::Gun, sprites->get(spBGun + (int)Type()), camera, nullptr, this);
  scene->addItem(GrItem);
}

int Unit::GunArty::getRange()
{
  return 10.0;
}

Cord Unit::GunArty::getCord()
{
  //to do
  Cord cord;
  cord.x = rect->x();
  cord.y = rect->y();
  return cord;
}

TargetType Unit::GunArty::getTargType()
{
  return TargetType::Cord;
}

void Unit::GunArty::attac(void *targ)
{
  if (interval) interval--;
  if (targ != nullptr)
  {
    Cord* cordTarg = static_cast<Cord*>(targ);
    GoVector vect;
    vect.addPos(cordTarg);
    a = vect.getA();
    if (interval == 0)
    {
      Cord cord = getCord();
      Ammo* ammo = new Ammo(cord.x, cord.y, 10.0, 70+point*10, 0.1, scene, camera, sprites, *cordTarg, AmmoType::Arty);
      maps->addAmmo((BaseAmmo*)ammo);
      interval = 12;
    }
    delete cordTarg;
  }
}

gunType Unit::GunArty::Type()
{
  return gunType::Arty;
}

void Unit::GunArty::updataGr()
{
  Cord cord = getCord();
  GrItem->setRealPos(cord.x,cord.y, a);
  if (interval > 0) interval--;
}
