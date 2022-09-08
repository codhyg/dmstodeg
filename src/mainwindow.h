#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void calculate_pressed();
    void reverse_pressed();
    int intInput(const QString& s);
    double dmsToDegConversion(int deg, int min, int sec);
    void switchAnimation(QWidget* w1, QWidget* w2);

};
#endif // MAINWINDOW_H
