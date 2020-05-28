#ifndef MYSCENE_H
#define MYSCENE_H
#include "collres.h"
#include "brain.h"
#include "grapcollitem.h"

class MyScene: public QGraphicsScene
{
  Q_OBJECT

public:
  explicit MyScene(const Sprite* sprite, Camera* camera, User* user, QObject* parent=0);
  ~MyScene();

private:
  User* user;
  Camera* camera;
  std::vector <GrapCollItem*> foc;
  const Sprite* sprite;
  DetectedP* GrItem = nullptr;
  bool press = false;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // MYSCENE_H
