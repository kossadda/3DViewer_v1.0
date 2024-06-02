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
    void on_Zoom_valueChanged(int position);
    void on_X_rotate_valueChanged(int position);
    void on_Y_rotate_valueChanged(int position);
    void on_Z_rotate_valueChanged(int position);
    void on_X_move_valueChanged(int position);
    void on_Y_move_valueChanged(int position);
    void on_Z_move_valueChanged(int position);
    void on_reset_clicked();
    void update_vertex();

private:
    Ui::MainWindow *ui;
    QPoint startPos;
    bool leftMouse = false;
    bool rightMouse = false;

public slots:
    void slotMousePress(QMouseEvent *event);
    void slotMouseMove(QMouseEvent *event);
    void slotMouseWheel(QWheelEvent *event);
};
#endif // MAINWINDOW_H
