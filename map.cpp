#include "map.h"

Block::Block(int x, int y, Sprite *sprite, QGraphicsScene *scene, Camera* camera)
  :x(x), y(x), scene(scene)
{
  std::cout << "Block create\n";
  grap = new GrapCollItem(x, y, 0, TypeObject::Block, sprite, camera);
  scene->addItem(grap);
}

Block::Block(Sprite *sprite, QGraphicsScene *scene, Camera *camera)
  :scene(scene)
{
  std::cout << "Block create\n";
  x = 0;
  y = 0;
  grap = new GrapCollItem(x, y, 0, TypeObject::Block, sprite, camera);
  scene->addItem(grap);
}

Block::~Block()
{
  for(auto it = units.begin();it != units.end(); ++it)
  {
    delete it->second;
  }

  scene->removeItem(grap);
  delete grap;
}

void Block::addUnit(Unit *unit)
{
  units[unit] = unit;
}

void Block::delUnit(Unit *unit)
{
  units.erase(unit);
}

void Block::act()
{
  for(auto it = units.begin();it != units.end(); ++it)
  {
    it->second->act();
  }
}

void Block::move()
{
  for(auto it = units.begin();it != units.end(); ++it)
  {
    it->second->move();
  }
}

void Block::dead()
{
  for(auto it = units.begin();it != units.end(); ++it)
  {
    it->second->dead();
    }
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
  for (auto it = mapBlock.begin();it != mapBlock.end(); ++it)
  {
    it->second->act();
  }
  for (auto it = mapBlock.begin();it != mapBlock.end(); ++it)
  {
    it->second->move();
  }
  for (auto it = mapBlock.begin();it != mapBlock.end(); ++it)
  {
    it->second->dead();
  }
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
