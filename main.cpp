#include "collres.h"

#include "mainwindow.h"


#ifdef __WIN32__
   WORD versionWanted = MAKEWORD(1, 1);
   WSADATA wsaData;
   WSAStartup(versionWanted, &wsaData);
#endif

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
