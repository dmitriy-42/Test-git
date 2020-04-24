#ifndef CAMERA_H
#define CAMERA_H


class Camera
{
public:
  Camera();
  double getX();
  double getY();
  double getA();
  double getH();
private:
  double x,y;
};

#endif // CAMERA_H
