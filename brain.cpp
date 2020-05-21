#include "brain.h"

Brain::Brain(std::vector <HaveGun> * gun, std::vector <HaveBuild> * build,
             BaseMoveType move, QRectF* rect, double maxRAttac,
             double maxRBuild)
  :gun(gun), build(build), move(move), rect(rect), maxRAttac(maxRAttac), maxRBuild(maxRBuild)
{}

Brain::~Brain()
{
  while (commands.size())
  {
    delete commands.top();
    commands.pop();
  }
  while (indTask.size())
  {
    indTask.pop();
  }
  delete gun;
  delete build;
  if (buildUnitList != nullptr)
  {
    for(int i = 0; i < (int)buildUnitList->size(); i++)
    {
      delete buildUnitList->at(i);
    }
    delete buildUnitList;
  }
  delete rect;
}

void Brain::push(FullCommand *command)
{
  switch (command->com)
  {
    case Command::BuildCircle: isCircle = true; break;
    case Command::NotBuildCircle: isCircle = false; break;
    case Command::Pass: break;
    case Command::BuildUnit:
      if (buildUnitList == nullptr)
      {
        buildUnitList = new std::vector <UnitDataBuild*>;
      }
      buildUnitList->push_back(command->buildUnit);
      break;
    default:
      commands.push(command);
  }
}

GoVector* Brain::Move()
{
  FullCommand* com;
  GoVector* vect = new GoVector;
  if (commands.size()) com = commands.top();
  else if (indTask.size()) com = indTask.top();
  else return vect;
  Cord cord;
  cord.x = (double)rect->x();
  cord.y = (double)rect->y();

  if (route == nullptr)
  {
    Cord* d = nullptr;
    switch (com->com)
    {
    case Command::Patrol:
        route = searchRoute(com->cord->at(iPatrol), 0);
        break;
    case Command::Build:
    case Command::RmBuild:
        route = searchRoute(com->cord->at(0), maxRBuild);
        break;
    case Command::Attack:
        if (com->target == TargetType::Cord)
          route = searchRoute(com->cord->at(0), maxRAttac);
        else
        {
          d = com->targetUnit->getCord();
          route = searchRoute(d, maxRAttac);
        }
        break;
    case Command::Go:
        route = searchRoute(com->cord->at(0), 0);
        break;
    default: break;
    }

    if (route != nullptr)
    {
      cord.x = route->top()->x - cord.x;
      cord.y = route->top()->y - cord.y;
    }
    vect->addPos(&cord);
    delete d;
  }
  else
  {
    vect->addPos(cord.y - route->top()->y, cord.x - route->top()->x, 0);
  }

  return vect;
}

Cord *Brain::attack(Cord, double r)
{
  FullCommand* com;
  if (commands.size()) com = commands.top();
  else if (indTask.size()) com = indTask.top();
  else return nullptr;
  if (com->com == Command::Attack)
  {
    Cord* cord = new Cord;
    switch (commands.top()->target) {
    case TargetType::Cord:
      cord->x = commands.top()->cord->at(0)->x;
      cord->y = commands.top()->cord->at(0)->y;
      break;
    default: break;
    }

    double x = (double)rect->x() - cord->x;
    double y = (double)rect->y() - cord->y;
    double dist = sqrt(x*x+y*y);


    if (r > dist) return cord;

  }
  return nullptr;
}

Unit *Brain::attackUnit(Cord, double)
{
  return nullptr;
}

std::stack<Cord*> *Brain::searchRoute(Cord * cord, double r)
{
  r *= 0.99;
  std::stack<Cord*> * routeCord = new std::stack<Cord*>;
  GoVector vect;
  Cord* myCord = new Cord;
  myCord->x = cord->x - (double)rect->x();
  myCord->y = cord->y - (double)rect->y();
  vect.addPos(myCord);
  if (vect.getSpeed() > r) vect.setSpeed(vect.getSpeed() - r);
  myCord->x = vect.getX() + (double)rect->x();
  myCord->y = vect.getY() + (double)rect->y();

  routeCord->push(myCord);
  return routeCord;
}
