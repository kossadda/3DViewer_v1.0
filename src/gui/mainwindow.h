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

private slots:
    void on_eyeXplus_clicked();
    void on_eyeXminus_clicked();
    void on_eyeYplus_clicked();
    void on_eyeYminus_clicked();
    void on_eyeZplus_clicked();
    void on_eyeZminus_clicked();
    void on_centerXplus_clicked();
    void on_centerXminus_clicked();
    void on_centerYplus_clicked();
    void on_centerYminus_clicked();
    void on_centerZplus_clicked();
    void on_centerZminus_clicked();
    void on_upXplus_clicked();
    void on_upXminus_clicked();
    void on_upYplus_clicked();
    void on_upYminus_clicked();
    void on_upZplus_clicked();
    void on_upZminus_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
