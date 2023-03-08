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
    bool dmsToDegState{true};

private slots:
    void calculate_pressed();
    void reverse_pressed();
    int intInput(const QString& s);
    void switchAnimation(QWidget* w1, QWidget* w2);
    void calcDmsToDeg();
    void calcDegToDms();
    bool eventFilter(QObject *object, QEvent *event);
    void showAboutWindow();
    void clearAllFields();

};
#endif // MAINWINDOW_H
