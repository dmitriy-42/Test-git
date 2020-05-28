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

#include <QGraphicsSceneMouseEvent>


const double PI = 3.14159265;
const int MaxGun = 10;
const int MaxUser = 8;
const double E = 0.0001; //Точность сравнения дробных чисел


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

enum class ResourceType{T1,T2,T3,T4,T5, D1,D2,D3,D4,D5, Plate, Elect, Mech, MicroFab, Engine};
const int lenResType = 13; //Количество видов ресурсов

enum class AmmoType{Def, Arty, Rocket};
enum class HaveGun{None, Air, Land, Water};
enum class HaveBuild{None, Build, Unit};
enum class TargetType{Unit, Build, Cord};
enum class Command{Pass, Go, Attack, Build, RmBuild, BuildUnit, Patrol, BuildCircle, NotBuildCircle};
enum class BuildType{MainBuild, Recycler, PlateFab};
enum class TypeObject {Gun, Unit, UnitAir, Block, Ammo, Resource, Building, Stone};
enum class TypeGrap {Detect, GrapCollItem, Icon, Kastul};
enum class TypeBlock{Default};

enum class gunType{Gun, Minigun, Arty, AntiAir/*Rocket*/}; // Изменения вроде ArrmorType{Light=1, ...}
enum class ArrmorType{Light, Medium, Heavy, Over};         // Могут ривести к перезаписи одного спрайта другим
enum class MoveType{Wheels, Tracks, Plane, Jet};           //

enum class BaseMoveType{None, Air, Land}; //Деление на воздушных, наземных и тех кто не может перемещяться.

enum class Color{Green, Blue, Orange, Red, Violet, Yellow};

struct FullResource
{
  int i;
  ResourceType type;
};

struct Resources
{
  FullResource res[20];
  int len;
};

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
  unsigned long long id;
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
  unsigned long long id;
};

struct UnitData
{
  double x; double y; double a; double health;
  ArrmorType arrmor; MoveType move; gunType guns[MaxGun];
  int aGuns[MaxGun]; QGraphicsScene* scene;
  unsigned long long id;
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
  QImage* foc;
  double w, h; // not pixel (real w, h)
  unsigned long long id;
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
const int spBNone = spBResIcon + spResIcon;
const int spNone = 1;
const int spLen = spBNone + spNone;

#endif // COLLRES_H

