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
    QValidator *int360Validator = new QIntValidator(0, 359, this);
    QValidator *int60Validator = new QIntValidator(0, 59, this);
    ui->dmsDegField->setValidator(int360Validator);
    ui->dmsMinutesField->setValidator(int60Validator);
    ui->dmsSecondsField->setValidator(int60Validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_pressed()
{
    std::cout << "calculate button pressed" << '\n';
    QString degEditText = ui->degField->text();
    std::cout << degEditText.toStdString().c_str() << '\n';
    degEditText = ui->dmsDegField->text();
    std::cout << degEditText.toStdString().c_str() << '\n';
    degEditText = ui->dmsMinutesField->text();
    std::cout << degEditText.toStdString().c_str() << '\n';
    degEditText = ui->dmsSecondsField->text();
    std::cout << degEditText.toStdString().c_str() << '\n';
}

void MainWindow::reverse_pressed()
{
    std::cout << "reverse button pressed" << '\n';
}
