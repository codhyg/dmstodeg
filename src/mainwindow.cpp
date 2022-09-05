#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QIntValidator>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));

    //SIGNALS AND SLOTS
    connect(ui->calculateButton,SIGNAL(released()),this,SLOT(calculate_pressed()));
    connect(ui->reverseButton,SIGNAL(released()),this,SLOT(reverse_pressed()));

    //UI ITEMS CONFIG
    ui->spinBoxDeg->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxSec->setButtonSymbols(QAbstractSpinBox::NoButtons);

    ui->spinBoxDeg->setFocus();
    ui->spinBoxDeg->selectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_pressed()
{
    std::cout << "calculate button pressed" << '\n';

    int deg{ ui->spinBoxDeg->text().toInt() };
    std::cout << deg << '\n';

    int min{ ui->spinBoxMin->text().toInt()};
    std::cout << min << '\n';

    int sec{ ui->spinBoxSec->text().toInt() };
    std::cout << sec << '\n';

    ui->degField->setText(QString().asprintf("%0.4f", dmsToDegConversion(deg, min, sec)));
}

void MainWindow::reverse_pressed()
{
    std::cout << "reverse button pressed" << '\n';
}

int MainWindow::intInput(const QString& s)
{
    return s.toInt();
}

double MainWindow::dmsToDegConversion(int deg, int min, int sec)
{
    const int sixty{ 60 }; //60 seconds in one minute, 60 minutes in one degree

    return (double)deg + ((double)sec/sixty + (double)min)/sixty;
}
