#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->calculateButton,SIGNAL(released()),this,SLOT(calculate_pressed()));
    connect(ui->reverseButton,SIGNAL(released()),this,SLOT(reverse_pressed()));
    ui->spinBoxDeg->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxSec->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_pressed()
{
    std::cout << "calculate button pressed" << '\n';

    int a{ ui->spinBoxDeg->text().toInt() };
    std::cout << a << '\n';

    int b{ ui->spinBoxMin->text().toInt()};
    std::cout << b << '\n';

    int c{ ui->spinBoxSec->text().toInt() };
    std::cout << c << '\n';

    ui->degField->setText(QString::number(intSum(a, b, c)));
}

void MainWindow::reverse_pressed()
{
    std::cout << "reverse button pressed" << '\n';
}

int MainWindow::intInput(const QString& s)
{
    return s.toInt();
}

int MainWindow::intSum(int a, int b, int c)
{
    return a + b + c;
}
