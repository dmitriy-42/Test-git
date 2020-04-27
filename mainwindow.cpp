#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  ui->graphicsView_2->setScene(scene);

  connect(ui->close,SIGNAL(clicked()),qApp,SLOT(quit()));
  connect(ui->mapEdit,SIGNAL(clicked()),this,SLOT(initMapEdit()));
  connect(ui->mainMenu,SIGNAL(clicked()),this,SLOT(exitMapEdit()));

  sprites = new Sprites;
  camera = new Camera;
  myMap = new Map(scene, camera, sprites);

  Sprite* sprite = new Sprite;
  sprite->tex = new QImage(":/qt4logo.png");
  sprite->h = 1.0;
  sprite->w = 1.0;

  sprites->create(5);
  sprites->append(sprite);

  timer1 = new QTimer(this);
  connect(timer1, SIGNAL(timeout()), scene, SLOT(advance()));

  // test
  Block* block = new Block(1, 1, sprites->get(0), scene, camera);
  std::cout << sprites->get(0)->tex->width() << "\n";
  myMap->set(block);
}

MainWindow::~MainWindow()
{
  delete myMap;
  delete ui;
  delete camera;
  delete sprites;
}


void MainWindow::initMapEdit()
{
  ui->stackedWidget->setCurrentIndex(3);
  timer1->start(100);
}

void MainWindow::exitMapEdit()
{
  ui->stackedWidget->setCurrentIndex(0);
  timer1->stop();
}
