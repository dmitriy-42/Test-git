#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView_2->setScene(scene);

  ui->graphicsView_2->setSceneRect(-200,-200,400,400);

  /*
  ui->graphicsView_2->setRenderHint(QPainter::Antialiasing, false);
  ui->graphicsView_2->setDragMode(QGraphicsView::RubberBandDrag);
  ui->graphicsView_2->setOptimizationFlags(QGraphicsView::DontSavePainterState);
  ui->graphicsView_2->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
  ui->graphicsView_2->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  */


  connect(ui->close,SIGNAL(clicked()),qApp,SLOT(quit()));
  connect(ui->mapEdit,SIGNAL(clicked()),this,SLOT(initMapEdit()));
  connect(ui->mainMenu,SIGNAL(clicked()),this,SLOT(exitMapEdit()));

  sprites = new Sprites;
  camera = new Camera;
  myMap = new Map(scene, camera, sprites);

  kostul = new Kostul(myMap);
  scene->addItem(kostul);

  sprites->create(spLen);

  sprites->set(0, new QImage(":/block1.png"), 1.0);
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

  UnitDataBuild buildunit;
  buildunit.lenGun = 1;
  buildunit.guns[0] = gunType::Arty;
  buildunit.arrmor = ArrmorType::Heavy;
  buildunit.move = MoveType::Tracks;

  Unit* unit = new Unit(&buildunit,0,0,scene,camera,sprites,myMap);
  myMap->addUnit(unit);
  buildunit.guns[0] = gunType::Gun;
  buildunit.arrmor = ArrmorType::Light;
  buildunit.move = MoveType::Wheels;

  unit = new Unit(&buildunit,0.5,0.5,scene,camera,sprites,myMap);
  myMap->addUnit(unit);
}

MainWindow::~MainWindow()
{
  delete myMap;
  delete ui;
  delete camera;
  delete sprites;

  delete kostul;
}


void MainWindow::initMapEdit()
{
  ui->stackedWidget->setCurrentIndex(3);
  timer1->start(40);
}

void MainWindow::exitMapEdit()
{
  ui->stackedWidget->setCurrentIndex(0);
  timer1->stop();
}
