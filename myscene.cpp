#include "myscene.h"



MyScene::MyScene(const Sprite *sprite, Camera* camera, User* user, QObject *parent)
  :QGraphicsScene(parent), user(user), camera(camera), sprite(sprite)
{
  GrItem = new DetectedP(0, 0, sprite);
  this->addItem(GrItem);
}

MyScene::~MyScene()
{

}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  std::cout << event->button() << " " << press << "\n";
  if (event->button() == 1)
  {
    if (press)
    {
      if (foc.size())
        {
          std::cout << "clear\n";
          for (int i = 0; i < (int)foc.size(); i++)
            foc[i]->setFoc(false);
          foc.clear();
        }
      QList <QGraphicsItem *> collList = this->collidingItems(GrItem);
      for (int i = 0; i < collList.size();i++)
      {
        if (static_cast<Grap*>(collList[i])->getTypeGrap() == TypeGrap::GrapCollItem
            and static_cast<GrapCollItem*>(collList[i])->getType() != TypeObject::Block)
        {
          static_cast<GrapCollItem*>(collList[i])->setFoc(true);
          //if (static_cast<GrapCollItem*>(collList[i])->getId() == user->getId())
            foc.push_back(static_cast<GrapCollItem*>(collList[i]));
        }
      }
      press = false;
    }
    else
      press = true;
  }

  if (event->button() == 2)
  {
    if (press)
    {
      press = false;
    }

    if (foc.size())
    {
      DetectedP* detect = new DetectedP(event->scenePos().x()-20, event->scenePos().y()-20, sprite);
      detect->setPos(event->scenePos().x()+20, event->scenePos().y()+20);

      bool attac = false;

      double x = event->scenePos().x();
      double y = event->scenePos().y();

      //Формула из QRectF GrapCollItem::boundingRect() последняя строчка.

      double h = camera->getH();
      double realX = x * h + camera->getX();
      double realY = y * h + camera->getY();

      QList <QGraphicsItem *> collList = this->collidingItems(detect);
      for (int i = 0; i < collList.size();i++)
      {
        if (static_cast<Grap*>(collList[i])->getTypeGrap() == TypeGrap::GrapCollItem
            and static_cast<GrapCollItem*>(collList[i])->getType() != TypeObject::Block)
        {
          if ((static_cast<GrapCollItem*>(collList[i])->getId() != user->getId()))
          {
            attac = true;
            break;
          }
          std::cout << "Detect " << (int)(static_cast<GrapCollItem*>(collList[i])->getType()) << '\n';
        }
      }

      FullCommand* com = new FullCommand;
      Cord* cord = new Cord;
      cord->x = realX;
      cord->y = realY;
      std::vector <Cord*> * vec = new std::vector <Cord*>;
      vec->push_back(cord);
      com->cord = vec;
      com->target = TargetType::Cord;
      if (attac) com->com = Command::Attack;
      else com->com = Command::Go;

      for (int i = 0; i < (int)foc.size(); i++)
      {
        if (foc[i]->getBrain() != nullptr)
        {
          foc[i]->getBrain()->clear();
          foc[i]->getBrain()->push(com);
        }
      }
    }
  }
}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (GrItem != nullptr)
    {
      GrItem->setPos(event->scenePos().x(), event->scenePos().y());
    }
}

