#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "collres.h"

#include "sprite.h"
#include "camera.h"
#include "connect.h"
#include "map.h"


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
  Kostul* kostul;
  QTimer* timer1;
  QTimer* timerMap;
  Sprites* sprites;
  Camera* camera;
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  Connect* con;
  Map* myMap;
private slots:
  void initMapEdit();
  void exitMapEdit();
};


#endif // MAINWINDOW_H
