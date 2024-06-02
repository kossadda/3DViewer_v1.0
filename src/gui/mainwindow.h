#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>

#include "./glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    unsigned int check_sliders();

private slots:
    void on_Zoom_sliderMoved(int position);
    void on_X_rotate_sliderMoved(int position);
    void on_Y_rotate_sliderMoved(int position);
    void on_Z_rotate_sliderMoved(int position);
    void on_X_move_sliderMoved(int position);
    void on_Y_move_sliderMoved(int position);
    void on_Z_move_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
