#include <iostream>
#include "mainwindow.h"
#include "../build_number.hpp"
#include "../include/config.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //report version
    std::cout << argv[0] << " Version " << dmstodeg_VERSION_MAJOR << '.' << dmstodeg_VERSION_MINOR << '.'
    << dmstodeg_VERSION_PATCH << '.' << BUILD_NUMBER << std::endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
