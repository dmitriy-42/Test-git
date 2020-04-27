#ifndef MAP_H
#define MAP_H
#include "units.h"
#include "grapcollitem.h"
#include <QGraphicsScene>
#include <stack>
#include "sprite.h"

#include <map>
#include <utility>
typedef std::pair<int, int> Coord;

enum class TypeBlock{Default};

class Unit;


class Block
{
public:
  Block(int x, int y, Sprite *sprite, QGraphicsScene *scene, Camera* camera);
  Block(Sprite *sprite, QGraphicsScene *scene, Camera* camera);
  ~Block();
  void addUnit(Unit* unit);
  void delUnit(Unit* unit);

  void act();
  void move();
  void dead();

  int getX();
  int getY();

  void setX(int x);
  void setY(int y);
  void setPos(int x, int y);
private:
  GrapCollItem* grap;
  int x,y;
  QGraphicsScene *scene;
  std::map <Unit*, Unit*> units;
};

class Map
{
public:
  Map(QGraphicsScene *scene, Camera* camera, Sprites* sprites);
  ~Map();
  bool load(char*);
  void save(char*);
  void set(int x, int y, Block*);
  void set(Block*);
  Block* get(int x, int y);
  void clear();

  void start();
private:
  QGraphicsScene *scene;
  std::map <Coord, Block*> mapBlock;
  Camera* camera;
  Sprites* sprites;
};

#endif // MAP_H
