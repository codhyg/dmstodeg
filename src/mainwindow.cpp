#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QIntValidator>
#include <QShortcut>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), ui->spinBoxDeg, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), ui->spinBoxMin, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), ui->spinBoxSec, SLOT(setFocus()));

    //SIGNALS AND SLOTS
    connect(ui->calculateButton, SIGNAL(released()), this, SLOT(calculate_pressed()));
    connect(ui->reverseButton, SIGNAL(released()), this, SLOT(reverse_pressed()));

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
    switchAnimation(ui->degField, ui->widget);
    switchAnimation(ui->widget, ui->degField);
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

void MainWindow::switchAnimation(QWidget* w1, QWidget* w2)
{
    QPropertyAnimation *animation = new QPropertyAnimation(w1, "geometry");
    animation->setDuration(100);
    animation->setStartValue(w1->geometry());
    animation->setEndValue(QRect(w2->x(), w2->y(), w1->width(), w2->height()));
    animation->start();
}
