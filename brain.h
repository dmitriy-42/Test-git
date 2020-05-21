#ifndef BRAIN_H
#define BRAIN_H
#include "collres.h"

#include "govector.h"
#include "units.h"
#include "build.h"



class Brain
{
public:
  Brain(std::vector <HaveGun> * gun, std::vector <HaveBuild> * build,
        BaseMoveType move, QRectF* rect, double maxRAttac,
        double maxRBuild);
  ~Brain();
  void push(FullCommand* command);
  void clear();

  std::stack <Command> * getHaveCommand();  //Какие комманды можно использовать
  std::stack <FullCommand> * getCommands(); //Copy commands
  GoVector* Move();
  Cord* attack(Cord, double r);     //Unit land and build
  Unit* attackUnit(Cord, double r); //Unit air
  UnitDataBuild* buUnit();
  BuildDataBuild* buBuild();
private:
  std::stack <Cord*> * route = nullptr;

  std::stack <Cord*> * searchRoute(Cord*, double r);
  bool tryRoute(std::stack <Cord>);
  std::stack <FullCommand*> commands;
  std::stack <FullCommand*> indTask;
  Cord retCord;

  std::vector <HaveGun> * gun;
  std::vector <HaveBuild> * build;
  BaseMoveType move;
  std::vector <UnitDataBuild*> * buildUnitList = nullptr;
  bool isCircle = false; // Повтор (строительство юнитов)
  int iUnitList = 0;     // Счётчик
  int iPatrol = 0;       // Счётчик

  QRectF* rect;
  double maxRAttac;
  double maxRBuild;
};

#endif // BRAIN_H
