#ifndef BUILD_H
#define BUILD_H
#include "collres.h"
#include "brain.h"
#include "user.h"
#include "camera.h"

class Build
{
public:
  virtual BuildType getType() = 0;
  virtual ~Build() = default;
  virtual void act() = 0;
  virtual bool dead() = 0;
};

class Fabric: public Build
{
public:
  Fabric(User* user, BuildType type, Cord, QGraphicsScene* scene, Camera* camera, double health);
  void act() override;
  bool dead() override;
  BuildType getType() override;
protected:
  BuildType type;
  QGraphicsScene* scene;
  double health;
  GrapCollItem* GrItem;
  int interval;
  User* user;
  virtual int getInterval() = 0;
  virtual bool Start(User* user) = 0;
  virtual Resources ResPut() = 0;
  virtual Resources ResGet() = 0;
};

class Recycler: public Fabric
{
public:
  Recycler(User* user, Cord cord, QGraphicsScene* scene, Camera* camera);
private:
  ResourceType res;
  int getInterval() override;
  bool Start(User* user) override;
  Resources ResPut() override;
  Resources ResGet() override;
};

class PlateFab: public Fabric
{
public:
  PlateFab(User* user, Cord cord, QGraphicsScene* scene, Camera* camera);
private:
  int getInterval() override;
  bool Start(User* user) override;
  Resources ResPut() override;
  Resources ResGet() override;
};

class ElectFab: public Fabric
{
public:
  ElectFab(User* user, Cord cord, QGraphicsScene* scene, Camera* camera);
private:
  int getInterval() override;
  bool Start(User* user) override;
  Resources ResPut() override;
  Resources ResGet() override;
};

class MechFab: public Fabric
{
public:
  MechFab(User* user, Cord cord, QGraphicsScene* scene, Camera* camera);
private:
  int getInterval() override;
  bool Start(User* user) override;
  Resources ResPut() override;
  Resources ResGet() override;
};

class ProFab: public Fabric
{
public:
  ProFab(User* user, Cord cord, QGraphicsScene* scene, Camera* camera);
private:
  ResourceType res;
  int getInterval() override;
  bool Start(User* user) override;
  Resources ResPut() override;
  Resources ResGet() override;
};


#endif // BUILD_H
