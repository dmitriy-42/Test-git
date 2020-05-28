#ifndef SPTRITE_H
#define SPTRITE_H
#include "collres.h"

// Переделал 26 задание по программированию в класс для храниния ссылок на спрайты
// У задания было минимальное тестирование, по этому в классе могут содержаться ошибки

void IndexError(int index, const char* f);
/** Вызывается в случае выхода за пределы массива, выводит отчёт и завершает работу программы */



class Sprites
{
public:
  Sprites(QImage* foc, unsigned long long id=(unsigned long long)nullptr);
  ~Sprites();
  void create(int size);
  const Sprite* get(int index);
  void set(int index, Sprite* sprite);
  void resize(int newSize);
  void free();
  void append(Sprite* sprite);
  void set(int index, QImage* image, double sizeSprite);
  void del(int index);
  int getSize();

  bool spriteLoad();
private:
  unsigned long long id;
  QImage* foc;
  Sprite** data;
  int size;
};


#endif // SPTRITE_H
