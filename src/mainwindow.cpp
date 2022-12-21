#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QIntValidator>
#include <QShortcut>
#include <QPropertyAnimation>
#include <cmath>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), ui->spinBoxDeg, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_M), ui->spinBoxMin, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), ui->spinBoxSec, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::Key_Enter), this, SLOT(calculate_pressed()));

    //SIGNALS AND SLOTS
    connect(ui->calculateButton, SIGNAL(released()), this, SLOT(calculate_pressed()));
    connect(ui->reverseButton, SIGNAL(released()), this, SLOT(reverse_pressed()));
    QTimer::singleShot(0, ui->spinBoxDeg, SLOT(selectAll()));

    //UI ITEMS CONFIG
    ui->spinBoxDeg->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxMin->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxSec->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBoxDeg->installEventFilter(this);
    ui->spinBoxMin->installEventFilter(this);
    ui->spinBoxSec->installEventFilter(this);

    //this goes to IF section
    ui->spinBoxDeg->setFocus();
    ui->spinBoxDeg->selectAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate_pressed()
{
    if (dmsToDegState)
    {
        calcDmsToDeg();
    } else {
        calcDegToDms();
    }
}

void MainWindow::reverse_pressed()
{
    switchAnimation(ui->degField, ui->widget);
    switchAnimation(ui->widget, ui->degField);

    if (dmsToDegState)
    {
        QRegExp degRegex("(?:[0-1]?[0-9]?[0-9]|2[0-9][0-9]|3[0-5][0-9]|360)\\.(?:[0-9]?[0-9]?[0-9]?[0-9])");
        QRegExpValidator *decDegValidator = new QRegExpValidator(degRegex, this);
        ui->degField->setValidator(decDegValidator);
        ui->degField->setReadOnly(false);
        ui->degField->setFocus();
        ui->degField->selectAll();
        ui->spinBoxDeg->setReadOnly(true);
        ui->spinBoxMin->setReadOnly(true);
        ui->spinBoxSec->setReadOnly(true);

        dmsToDegState = false;
    } else {

        ui->spinBoxDeg->setFocus();
        ui->spinBoxDeg->selectAll();
        ui->degField->setReadOnly(true);
        ui->spinBoxDeg->setReadOnly(false);
        ui->spinBoxMin->setReadOnly(false);
        ui->spinBoxSec->setReadOnly(false);

        dmsToDegState = true;
    }
}

int MainWindow::intInput(const QString& s)
{
    return s.toInt();
}

void MainWindow::calcDmsToDeg()
{
    int deg{ ui->spinBoxDeg->text().toInt() };

    int min{ ui->spinBoxMin->text().toInt()};

    int sec{ ui->spinBoxSec->text().toInt() };

    ui->degField->setText(QString().asprintf("%0.4f", dmsToDegConversion(deg, min, sec)));
}

void MainWindow::calcDegToDms()
{
    const int sixty{ 60 }; //60 seconds in one minute, 60 minutes in one degree

    double decdeg{ ui->degField->text().toDouble() };
    double deg = floor(decdeg);
    double min = (decdeg - deg) * sixty ;
    double sec = (min - floor(min)) * sixty ;

    ui->spinBoxDeg->setValue(deg);
    ui->spinBoxMin->setValue(min);
    ui->spinBoxSec->setValue(sec);
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

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        if (object == ui->spinBoxDeg)
        {
            ui->spinBoxDeg->selectAll();
        }

        if (object == ui->spinBoxMin)
        {
            ui->spinBoxMin->selectAll();
        }

        if (object == ui->spinBoxSec)
        {
            ui->spinBoxSec->selectAll();
        }
    }
    return false;
}
