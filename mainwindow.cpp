#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  for (int i = 0; i < MaxUser; i++)
    {
      users[i] = nullptr;
    }
  ui->setupUi(this);

  //scene = new QGraphicsScene(this);



  connect(ui->close,SIGNAL(clicked()),qApp,SLOT(quit()));
  connect(ui->mapEdit,SIGNAL(clicked()),this,SLOT(initMapEdit()));
  connect(ui->mainMenu,SIGNAL(clicked()),this,SLOT(exitMapEdit()));

  User* user = new User(Color::Blue);

  sprites = new Sprites(new QImage("://sprite/Name1.png"));
  sprites->create(spLen);

  QImage* noneSprite = new QImage("://sprite/none.png");
  for (int i = 0; i < spLen; i++)
  {
    sprites->set(i, noneSprite, 1.0);
  }

  sprites->set(0, new QImage(":/block1.png"), 1.0);
  sprites->set(spBEffect, new QImage("://sprite/Detect.png"), 1.0/*Ignore*/);

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
  //sprites->set(spBAmmo, new QImage("://sprite/HT.png"), 0.1);
  sprites->set(spBGun + (int) gunType::Gun, new QImage("://sprite/gun.png"), 1.3);
  sprites->set(spBGun + (int) gunType::Arty, new QImage("://sprite/arty.png"), 3.0);
  sprites->set(spBAmmo, new QImage("://sprite/ammo.png"), 0.4);


  camera = new Camera;

  scene = new MyScene(sprites->get(spBEffect), camera, user, this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView->setSceneRect(-200,-200,400,400);

  ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);
  ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
  ui->graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  myMap = new Map(scene, camera, sprites);

  kostul = new Kostul(myMap);
  scene->addItem(kostul);





  timer1 = new QTimer(this);
  connect(timer1, SIGNAL(timeout()), scene, SLOT(advance()));

  // test

  /*
  Block* block0 = new Block(1, 1, sprites->get(0), scene, camera);
  myMap->set(block0);
  Block* block1 = new Block(0, 0, sprites->get(0), scene, camera);
  myMap->set(block1);
  */
  for (int i = -30; i < 30;i++)
  {
    for (int j = -30; j < 30;j++)
    {
      Block* block0 = new Block(i, j, sprites->get(0), scene, camera);
      myMap->set(block0);
    }
  }


  Cord cord;
  cord.x = 6.0;
  cord.y = 1.0;
  Recycler* rec = new Recycler(user, cord, scene, camera);
  myMap->addBuild(rec);
  users[0] = user;

  UnitDataBuild buildunit;
  buildunit.lenGun = 1;
  buildunit.guns[0] = gunType::Gun;
  buildunit.arrmor = ArrmorType::Medium;
  buildunit.move = MoveType::Tracks;

  Unit* unit = new Unit(&buildunit,0,0,scene,camera,users[0]->getSprite(),myMap);
  myMap->addUnit(unit);
  buildunit.guns[0] = gunType::Gun;
  buildunit.arrmor = ArrmorType::Light;
  buildunit.move = MoveType::Tracks;

  unit = new Unit(&buildunit,5.5, 5.5,scene,camera,users[0]->getSprite(), myMap);
  myMap->addUnit(unit);


  //Icon* icon = new Icon(1,1,20,sprites->get(spBNone));
  //scene->addItem(icon);



}

MainWindow::~MainWindow()
{
  delete myMap;
  delete ui;
  delete camera;
  delete sprites;

  delete kostul;
  for (int i = 0; i < MaxUser; i++)
    {
      delete users[i];
    }
}


void MainWindow::initMapEdit()
{
  ui->stackedWidget->setCurrentIndex(2);
  timer1->start(4000000);
}

void MainWindow::exitMapEdit()
{
  ui->stackedWidget->setCurrentIndex(0);
  timer1->stop();
}
