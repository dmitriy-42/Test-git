#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"


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

  camera = new Camera;
  MyMap = new Map(scene, camera);
}

MainWindow::~MainWindow()
{
  delete MyMap;
  delete ui;
  delete camera;
}


void MainWindow::initMapEdit()
{
  ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::exitMapEdit()
{
  ui->stackedWidget->setCurrentIndex(0);
}
