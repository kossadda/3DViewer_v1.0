#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

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
    void initSlide(QSlider *sl);
    void slideSlot(int value);
    void on_x_plus_clicked();
    void on_x_minus_clicked();
    void on_y_plus_clicked();
    void on_y_minus_clicked();
    void on_z_plus_clicked();
    void on_z_minus_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
