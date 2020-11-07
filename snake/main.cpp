#include <QApplication>
#include "snake.h"
#include "mainwindow.h"
int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  MainWindow w;

  w.showMaximized();
  /*
  window.setWindowTitle("Snake");

  window.raise();
  window.show();
  window.setFocus();*/
  return app.exec();
  }
