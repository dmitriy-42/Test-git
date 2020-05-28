#include "user.h"

User::User(unsigned long long commandId, unsigned long long id, Color color)
  :commandId(commandId), id(id), color(color)
{
  init();
}

User::User(unsigned long long id, Color color)
  :commandId((unsigned long long)this), id(id), color(color)
{
  init();
}

User::User(Color color)
  :commandId((unsigned long long)this), id((unsigned long long)this), color(color)
{
  init();
}

User::~User()
{
  for (int i = 0; i < lenResType; i++)
    {
      std::cout << "Res " << res[i].i << ' ' << i << "\n";
    }
}

Sprites *User::getSprite()
{
  return sprites;
}

unsigned long long User::getCommandId()
{
  return commandId;
}

unsigned long long User::getId()
{
  return id;
}

bool User::getRes(ResourceType type, int len)
{
  if (isRes(type, len))
  {
    res[(int)type].i -= len;
    return true;
  }
  return false;
}

bool User::isRes(ResourceType type, int len)
{
  return res[(int)type].i >= len;
}

void User::putRes(ResourceType type, int len)
{
  res[(int)type].i += len;
}

void User::init()
{
  sprites = new Sprites(new QImage("://sprite/Name1.png"), id);
  sprites->create(spLen);
  QImage* noneSprite = new QImage("://sprite/none.png");
  for (int i = 0; i < spLen; i++)
  {
    sprites->set(i, noneSprite, 1.0);
  }
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Light * spMove + (int)MoveType::Wheels,
               new QImage("://sprite/LW.png"), 2.0);
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Medium * spMove + (int)MoveType::Wheels,
               new QImage("://sprite/MW.png"), 3.0);
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Heavy * spMove + (int)MoveType::Wheels,
               new QImage("://sprite/HW.png"), 4.0);
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Light * spMove + (int)MoveType::Tracks,
               new QImage("://sprite/LT.png"), 2.0);
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Medium * spMove + (int)MoveType::Tracks,
               new QImage("://sprite/MT.png"), 3.0);
  sprites->set(spBArrmorAndMove + (int)ArrmorType::Heavy * spMove + (int)MoveType::Tracks,
               new QImage("://sprite/HT.png"), 4.0);
  sprites->set(spBAmmo, new QImage("://sprite/HT.png"), 0.1);
  sprites->set(spBGun + (int) gunType::Gun, new QImage("://sprite/gun.png"), 1.0);
  sprites->set(spBGun + (int) gunType::Arty, new QImage("://sprite/arty.png"), 1.5);
  sprites->set(spBAmmo, new QImage("://sprite/ammo.png"), 0.4);
  res = new FullResource[lenResType];
  for (int i = 0; i < lenResType; i++)
  {
    res[i].i = 100;
    res[i].type = (ResourceType)i;
  }
}
