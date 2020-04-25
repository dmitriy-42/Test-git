#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "sprite.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include "camera.h"
#include "connect.h"
#include "map.h"

#include "map"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
private:
  Camera* camera;
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  Connect* con;
  Map* MyMap;
private slots:
  void initMapEdit();
  void exitMapEdit();
};


#endif // MAINWINDOW_H
