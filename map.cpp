#include "map.h"

Block::Block(int x, int y, Sprite *sprite, QGraphicsScene *scene, Camera* camera)
  :x(x), y(x), scene(scene)
{
  grap = new GrapCollItem(x, y, 0, TypeObject::Block, sprite, camera, nullptr, this);
  scene->addItem(grap);
}

Block::Block(Sprite *sprite, QGraphicsScene *scene, Camera *camera)
  :scene(scene)
{
  x = 0;
  y = 0;
  grap = new GrapCollItem(x, y, 0, TypeObject::Block, sprite, camera, nullptr, this);
  scene->addItem(grap);
}

Block::~Block()
{
  scene->removeItem(grap);
  delete grap;
}

int Block::getX()
{
  return x;
}

int Block::getY()
{
  return y;
}

void Block::setX(int x)
{
  this->x = x;
  grap->setX(x);
}

void Block::setY(int y)
{
  this->y = y;
  grap->setX(y);
}

void Block::setPos(int x, int y)
{
  this->x = x;
  this->y = y;
  grap->setRealPos(x, y, grap->getRealA());
}


Map::Map(QGraphicsScene *scene, Camera* camera, Sprites* sprites)
  :scene(scene), camera(camera), sprites(sprites)
{
  //to do
}

Map::~Map()
{
  for(auto it = units.begin();it != units.end(); ++it)
  {
    delete it->second;
  }
  clear();
}

void Map::clear()
{
  for (auto it = mapBlock.begin();it != mapBlock.end(); ++it)
  {
    delete it->second;
  }
  mapBlock.clear();
}

void Map::start()
{
  std::cout << "start\n";
  act();
  move();
  deadUnit.clear();
  dead();
}


bool Map::load(char*){return true;}
void Map::save(char*){}

void Map::set(int x, int y, Block* block)
{
  Coord crd = std::make_pair(x,y);
  mapBlock[crd] = block;
}

void Map::set(Block * block)
{
  Coord crd = std::make_pair(block->getX(), block->getY());
  mapBlock[crd] = block;
}

Block* Map::get(int x, int y)
{
  Coord crd = std::make_pair(x,y);
  try
  {
    return mapBlock.at(crd);
  }  catch (std::out_of_range &) {
    return nullptr;
  }
}


void Map::addUnit(Unit *unit)
{
  units[unit] = unit;
}

void Map::delUnit(Unit *unit)
{
  deadUnit.push_back(unit);

  units.erase(unit);
  delete unit;
}

void Map::addAmmo(BaseAmmo *ammo)
{
  ammos[ammo] = ammo;
}

void Map::delAmmo(BaseAmmo *ammo)
{
  this->ammos.erase(ammo);
  delete ammo; //virtual ~BaseAmmo();
}

void Map::act()
{

  for(auto it = ammos.begin();it != ammos.end(); ++it)
  {
    it->second->act();
  }

  for(auto it = units.begin();it != units.end(); ++it)
  {
    it->second->act();
  }

}

void Map::move()
{
  for(auto it = ammos.begin();it != ammos.end(); ++it)
  {
    it->second->move();
  }
  for(auto it = units.begin();it != units.end(); ++it)
  {
    it->second->move();
  }
}

void Map::dead()
{
  for(auto it = ammos.begin();it != ammos.end(); ++it)
  {
    if (it->second->dead()) delAmmo(it->second);
  }
  for(auto it = units.begin();it != units.end(); ++it)
  {
    if (it->second->dead()) delUnit(it->second);
  }
}
