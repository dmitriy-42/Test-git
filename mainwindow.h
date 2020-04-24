#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "connect.h"
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
  Ui::MainWindow *ui;
  QGraphicsScene *scene;
  Connect* con;
private slots:
  void initMapEdit();
  void exitMapEdit();
};


#endif // MAINWINDOW_H
