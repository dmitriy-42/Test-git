#include "camera.h"

Camera::Camera()
{
  x = 0.0;
  y = 0.0;
  a = 0.0;
  h = 1;
}

double Camera::getX(){return x;}
double Camera::getY(){return y;}
double Camera::getA(){return a;}
double Camera::getH(){return h;}
