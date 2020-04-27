#ifndef CAMERA_H
#define CAMERA_H
#include <QObject>


class Camera//: public  QObject
{
public:
  Camera();
  double getX();
  double getY();
  double getA();
  double getH();
private:
  double x,y,h,a;
//public slots:
};

#endif // CAMERA_H
