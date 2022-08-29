#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calculateButton,SIGNAL(released()),this,SLOT(calculate_pressed()));
    connect(ui->reverseButton,SIGNAL(released()),this,SLOT(reverse_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_pressed()
{
    std::cout << "calculate button pressed" << '\n';
}

void MainWindow::reverse_pressed()
{
    std::cout << "reverse button pressed" << '\n';
}
