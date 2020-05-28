#include "build.h"


Fabric::Fabric(User *user, BuildType type, Cord cord, QGraphicsScene* scene, Camera* camera, double health)
  :type(type), scene(scene), health(health), user(user)
{
  GrItem = new GrapCollItem(cord.x,cord.y,0,TypeObject::Building, user->getSprite()->get(spBBuild + (int)type), camera, nullptr, nullptr);
  scene->addItem(GrItem);
  interval = 0;
}

void Fabric::act()
{
  if (interval == 0)
    {
      if (Start(user))
      {
        Resources res = ResGet();
        for (int i = 0; i < res.len; i++)
        {
          if (not user->isRes(res.res[i].type, res.res[i].i))
            {
              return;
            }
        }
        for (int i = 0; i < res.len; i++)
        {
          user->getRes(res.res[i].type, res.res[i].i);
        }
        res = ResPut();
        for (int i = 0; i < res.len; i++)
        {
          user->putRes(res.res[i].type, res.res[i].i);
        }
        interval = getInterval();
      }
    }
  if (interval > 0) interval--;
}

bool Fabric::dead()
{
  health -= GrItem->getDamage();
  return health <= 0;
}

BuildType Fabric::getType()
{
  return type;
}

Recycler::Recycler(User *user, Cord cord, QGraphicsScene *scene, Camera *camera)
  :Fabric(user, BuildType::Recycler, cord, scene, camera, 1200)
{
  res = ResourceType::T1;
}


int Recycler::getInterval()
{
  return 3;
}

bool Recycler::Start(User *user)
{
  int i;
  for (i = 0; i < 5; i++)
    {
      if (not user->isRes((ResourceType)(i+5), 200))
        {
          res = (ResourceType)i;
          break;
        }
    }
  return i != 5;
}

Resources Recycler::ResPut()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = (ResourceType)((int)res + 5);
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}

Resources Recycler::ResGet()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = res;
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}



PlateFab::PlateFab(User *user, Cord cord, QGraphicsScene *scene, Camera *camera)
   :Fabric(user, BuildType::PlateFab, cord, scene, camera, 1600)
{}

int PlateFab::getInterval()
{
  return 10;
}

bool PlateFab::Start(User *user)
{
  return user->isRes(ResourceType::Plate, 200);
}

Resources PlateFab::ResPut()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::Plate;
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}

Resources PlateFab::ResGet()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::D1;
  FullResource fullres1;
  fullres1.i = 1;
  fullres1.type = ResourceType::D2;
  resource.len = 2;
  resource.res[0] = fullres;
  resource.res[1] = fullres1;
  return resource;
}

ElectFab::ElectFab(User *user, Cord cord, QGraphicsScene *scene, Camera *camera)
   :Fabric(user, BuildType::PlateFab, cord, scene, camera, 1600)
{}

int ElectFab::getInterval()
{
  return 15;
}

bool ElectFab::Start(User *user)
{
  return user->isRes(ResourceType::Elect, 200);
}

Resources ElectFab::ResPut()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::Elect;
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}

Resources ElectFab::ResGet()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::D5;
  FullResource fullres1;
  fullres1.i = 1;
  fullres1.type = ResourceType::D2;
  resource.len = 2;
  resource.res[0] = fullres;
  resource.res[1] = fullres1;
  return resource;
}


MechFab::MechFab(User *user, Cord cord, QGraphicsScene *scene, Camera *camera)
   :Fabric(user, BuildType::PlateFab, cord, scene, camera, 1600)
{}

int MechFab::getInterval()
{
  return 13;
}

bool MechFab::Start(User *user)
{
  return user->isRes(ResourceType::Mech, 200);
}

Resources MechFab::ResPut()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::Mech;
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}

Resources MechFab::ResGet()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::D2;
  FullResource fullres1;
  fullres1.i = 1;
  fullres1.type = ResourceType::D3;
  resource.len = 2;
  resource.res[0] = fullres;
  resource.res[1] = fullres1;
  return resource;
}


ProFab::ProFab(User *user, Cord cord, QGraphicsScene *scene, Camera *camera)
  :Fabric(user, BuildType::Recycler, cord, scene, camera, 2000)
{
  res = ResourceType::MicroFab;
}


int ProFab::getInterval()
{
  return 30;
}

bool ProFab::Start(User *user)
{
  int i;
  for (i = (int)ResourceType::MicroFab; i <= (int)ResourceType::Engine; i++)
    {
      if (not user->isRes((ResourceType)(i), 200))
        {
          res = (ResourceType)i;
          break;
        }
    }
  return i != 5;
}

Resources ProFab::ResPut()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = (ResourceType)(int)res;
  resource.len = 1;
  resource.res[0] = fullres;
  return resource;
}

Resources ProFab::ResGet()
{
  Resources resource;
  FullResource fullres;
  fullres.i = 1;
  fullres.type = ResourceType::Mech;
  FullResource fullres1;
  fullres1.i = 1;
  if (res == ResourceType::MicroFab)
    fullres1.type = ResourceType::Elect;
  else
    fullres1.type = ResourceType::Plate;
  resource.len = 2;
  resource.res[0] = fullres;
  resource.res[1] = fullres1;
  return resource;
}
