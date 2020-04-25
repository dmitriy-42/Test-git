#ifndef SPTRITE_H
#define SPTRITE_H
#include <QImage>
#include <iostream>

// Переделал 26 задание по программированию в класс для храниния ссылок на спрайты
// У задания было минимальное тестирование, по этому в классе могут содержаться ошибки

void IndexError(int index, const char* f);
/** Вызывается в случае выхода за пределы массива, выводит отчёт и завершает работу программы */

struct Sprite
{
  QImage tex;
  double w, h; // not pixel
};

class Sprites
{
public:
  Sprites();
  ~Sprites();
  void create(int size);
  Sprite* get(int index);
  void set(int index, Sprite* sprite);
  void resize(int newSize);
  void free();
  void append(Sprite* sprite);
  void del(int index);
  int getSize();

  bool spriteLoad();
private:
  Sprite** data;
  int size;
};


#endif // SPTRITE_H
