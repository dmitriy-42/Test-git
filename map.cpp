#include "map.h"

Block::Block(int x, int y, Sprite *sprite, QGraphicsScene *scene, Camera* camera)
  :x(x), y(x), scene(scene)
{
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


Map::Map(QGraphicsScene *scene, Camera* camera)
  :scene(scene), camera(camera)
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
