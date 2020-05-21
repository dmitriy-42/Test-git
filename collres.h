#ifndef COLLRES_H
#define COLLRES_H

/*
 * Это место было создано для решения проблем с использованием в разных файлах одних и тех же вещей.
 * Здесь происходит подключение всех библиотек
 * Здесь хранятся:
 * Глобальные константы (по типу числа pi)
 * Название всех классов
 * Все enum class
 * Все struct
*/

#include <QApplication>
#include <QFrame>
#include <iostream>
#include <vector>
#include <stack>
#include <QObject>
#include <cmath>
#include <QGraphicsItem>
#include <QPainter>
#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QImage>
#include <map>
#include <utility>


const double PI = 3.14159265;
const int MaxGun = 10;


class Unit;
class Build;
class Brain;
class Camera;
class GoVector;
class GrapCollItem;
class Detected;
class Grap;
class MainWindow;
class Block;
class Map;
class Sprites;
class Unit;
class BaseAmmo;
class Ammo;


enum class AmmoType{Def, Arty, Rocket};
enum class HaveGun{None, Air, Land, Water};
enum class HaveBuild{None, Build, Unit};
enum class TargetType{Unit, Build, Cord};
enum class Command{Pass, Go, Attack, Build, RmBuild, BuildUnit, Patrol, BuildCircle, NotBuildCircle};
enum class BuildType{};
enum class TypeObject {Gun, Unit, UnitAir, Block, Ammo, Resource, Building, Stone};
enum class TypeGrap {Detect, GrapCollItem, Kastul};
enum class TypeBlock{Default};

enum class gunType{Gun, Minigun, Arty, AntiAir/*Rocket*/}; // Изменения вроде ArrmorType{Light=1, ...}
enum class ArrmorType{Light, Medium, Heavy, Over};         // Могут ривести к перезаписи одного спрайта другим
enum class MoveType{Wheels, Tracks, Plane, Jet};           //

enum class BaseMoveType{None, Air, Land}; //Деление на воздушных, наземных и тех кто не может перемещяться.

struct BrainGun{
  HaveGun gun[MaxGun];
  double r[MaxGun];
  int len = 0;
};

struct BrainBuilder{
  HaveBuild build[MaxGun];
  double r[MaxGun];
  int len = 0;
};

struct Cord
{
  double x;
  double y;
};

struct BuildDataBuild
{
  int x;
  int y;
  int a;
  BuildType type;
};

struct gunSlot
{
  double x, y;
};

struct gunSlots
{
  int len;
  gunSlot slot[MaxGun];
};

struct UnitDataBuild // Данные для создания юнитов
{
  gunType guns[MaxGun];
  int lenGun;
  ArrmorType arrmor;
  MoveType move;
};

struct UnitData
{
  double x; double y; double a; double health;
  ArrmorType arrmor; MoveType move; gunType guns[MaxGun];
  int aGuns[MaxGun]; QGraphicsScene* scene;
};

struct FullCommand // Хранит команду и данные к ней (не все данные будут использованны (зависит от команды))
{
  Command com;
  TargetType target;
  //Build targetBuild;
  Unit* targetUnit = nullptr;
  std::vector <Cord*> * cord = nullptr;
  UnitDataBuild* buildUnit = nullptr;
  BuildDataBuild* buildBuild = nullptr;
};

struct Sprite
{
  QImage* tex;
  double w, h; // not pixel (real w, h)
};



const int spMap = 16;
const int spBArrmorAndMove = spMap;
const int spArrmor = 8;
const int spMove = 8;
const int spBGun = spBArrmorAndMove + spArrmor * spMove;
const int spGun = 8;
const int spBBuild = spBGun + spGun;
const int spBuild = 16;
const int spBRessors = spBBuild + spBuild;
const int spRessors = 8;
const int spBAmmo = spBRessors + spBRessors;
const int spAmmo = 4;
const int spBEffect = spBAmmo + spAmmo;
const int spEffect = 8;
const int spBCommand = spBEffect + spEffect;
const int spCommand = 16;
const int spBResIcon = spBCommand + spCommand;
const int spResIcon = 32;
const int spLen = spBResIcon + spResIcon;

#endif // COLLRES_H

