#include <QApplication>
#include <QLabel>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  QIcon appIcon(":assets/Viewer.icns");
  w.setWindowIcon(appIcon);
  w.show();
  return a.exec();
}
