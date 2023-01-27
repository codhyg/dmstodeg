#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QShortcut>
#include "../build_number.hpp"
#include "../include/config.h"

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));

    QString dmstodeg_version = QString("<p><b>dmstodeg</b><br/>ver. %1.%2.%3<br/>build %4</p>").arg(dmstodeg_VERSION_MAJOR).arg(dmstodeg_VERSION_MINOR).arg(dmstodeg_VERSION_PATCH).arg(BUILD_NUMBER);
    ui->aboutLabel->setText(dmstodeg_version);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
