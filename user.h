#ifndef USER_H
#define USER_H
#include "collres.h"
#include "sprite.h"

class User
{
public:
  User(unsigned long long commandId, unsigned long long id, Color color);
  User(unsigned long long id, Color color);
  User(Color color);
  ~User();

  Sprites* getSprite();
  unsigned long long getCommandId();
  unsigned long long getId();

  bool getRes(ResourceType type, int len);
  bool isRes(ResourceType type, int len);
  void putRes(ResourceType type, int len);
private:
  FullResource* res;
  void init();
  unsigned long long commandId;
  unsigned long long id; //основан на ссылке
  Sprites* sprites;
  Color color;
};

#endif // USER_H
