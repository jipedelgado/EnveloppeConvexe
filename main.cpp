/* @author : jipedelgado@gmail.com
 * Qt Creator 3.1.0 (opensource)
 * Basé sur Qt 5.2.1 (MSVC 2010, 32 bit)
 *
 * */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
