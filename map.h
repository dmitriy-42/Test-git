#ifndef MAP_H
#define MAP_H
#include "units.h"
#include "grapcollitem.h"
#include <QGraphicsScene>
#include <stack>

#include <map>
#include <utility>
typedef std::pair<int, int> Coord;

enum class TypeBlock{Default};


class Block
{
public:
  Block(int x, int y, Sprite *sprite, QGraphicsScene *scene, Camera* camera);
  ~Block();
  void addUnit(Unit* unit);
  void delUnit(Unit* unit);
private:
  GrapCollItem* grap;
  int x,y;
  QGraphicsScene *scene;
  std::map <Unit*, Unit*> units;
};

class Map
{
public:
  Map(QGraphicsScene *scene, Camera* camera);
  ~Map();
  bool load(char*);
  void save(char*);
  void set(int x, int y, Block*);
  Block* get(int x, int y);
  void clear();
private:
  QGraphicsScene *scene;
  std::map <Coord, Block*> mapBlock;
  Camera* camera;
};

#endif // MAP_H
