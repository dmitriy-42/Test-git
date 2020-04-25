#include "sprite.h"


void IndexError(Sprites* sprites, int index, const char* f)
{
  std::cerr << "IndexErorr: index = " <<  index << ", size = " << sprites->getSize() << ", function = " << f << "\ndata:\n";
  srand(time(NULL));
  if (not rand()%21) std::cout << "\n03:14:08 19.01.2033\n";
  exit(1);
}


Sprites::Sprites()
{
  data = nullptr;
}

Sprites::~Sprites()
{
  free();
}

void Sprites::create(int size)
{
  if (data != nullptr) free();
  data = new Sprite* [size];
  this->size = size;
  for (int i = 0;i<size;i++){data[i] = nullptr;}
}

Sprite* Sprites::get(int index)
{
  if (size < index or index + size < 0) IndexError(this, index, "get");
  if (index < 0) index += size;
  return data[index];
}

void Sprites::set(int index, Sprite* sprite)
{
  if (size < index or index + size < 0) IndexError(this, index, "set");
  if (index < 0) index += size;
  data[index] = sprite;
}

void Sprites::resize(int newSize)
{
  if (data == nullptr) create(newSize);
  else
  {
    Sprite** olddata = data;
    data = new Sprite* [newSize];
    int i = 0;
    for (;i<newSize;i++)
    {
      if (i<size) data[i] = olddata[i];
      else data[i] = nullptr;
    }

    for (; i < size; i++)
    {
      if (olddata[i] == nullptr) delete olddata[i];
    }
    delete olddata;
    size = newSize;
  }
}

void Sprites::free()
{
  for (int i = 0; i < size; i++)
  {
    del(i);
  }
  delete data;
  data = nullptr;
  size = 0;
}

void Sprites::append(Sprite* sprite)
{
  if (data == nullptr) create(1);
  int i = size-1;
  for (;0 <= i;i--)
  {
    if (get(i) != nullptr)
    {
      if (i == size-1)
        { resize(size*15/10); append(sprite); break;}
      else
        {set(i+1, sprite); break;};
    }
  }
  if (i == -1) set(0, sprite);
}

void Sprites::del(int index)
{
  if (size < index or index + size < 0) IndexError(this, index, "del");
  if (index < 0) index += size;
  if (data[index] == nullptr) delete data[index];
}

int Sprites::getSize()
{
  return size;
}
