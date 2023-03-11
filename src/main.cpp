#include <iostream>
#include "mainwindow.h"
#include "../build_number.hpp"
#include "../include/config.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
