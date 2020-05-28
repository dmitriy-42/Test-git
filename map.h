#ifndef MAP_H
#define MAP_H
#include "collres.h"

#include "units.h"
#include "grapcollitem.h"
#include "sprite.h"
#include "ammo.h"
#include "build.h"
typedef std::pair<int, int> Coord;
// Используестя map в качестве словоря, возможно стоило создать что то более подходящее... Но времени может не хватить.


class Block
{
public:
  Block(int x, int y, const Sprite *sprite, QGraphicsScene *scene, Camera* camera);
  Block(const Sprite *sprite, QGraphicsScene *scene, Camera* camera);
  ~Block();

  int getX();
  int getY();

  void setX(int x);
  void setY(int y);
  void setPos(int x, int y);
private:
  GrapCollItem* grap;
  int x,y;
  QGraphicsScene *scene;
};


class Map: public QObject
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

  void addUnit(Unit* unit);
  void delUnit(Unit* unit);
  void addAmmo(BaseAmmo* ammo);
  void delAmmo(BaseAmmo* ammo);
  void addBuild(Build* build);
  void delBuild(Build* build);

  void start();
private:
  std::vector <Unit*> deadUnit;

  void act();
  void move();
  void dead();

  QGraphicsScene *scene;
  std::map <Unit*, Unit*> units;
  std::map <BaseAmmo*, BaseAmmo*> ammos;
  std::map <Build*, Build*> build;
  std::map <Coord, Block*> mapBlock;
  Camera* camera;
  Sprites* sprites;
};


#endif // MAP_H
