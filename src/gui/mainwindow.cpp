#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Zoom_sliderMoved(int position)
{
    float change = (float)position / 100.0f;
    scale_model(&ui->GL->data, &ui->GL->object, change, change, change);
    ui->GL->update();
}

void MainWindow::on_X_rotate_sliderMoved(int position)
{
    float change = (float)position * RAD;
    x_rotate_model(&ui->GL->data, &ui->GL->object, change);
    ui->GL->update();
}

void MainWindow::on_Y_rotate_sliderMoved(int position)
{
    float change = (float)position * RAD;
    y_rotate_model(&ui->GL->data, &ui->GL->object, change);
    ui->GL->update();
}

void MainWindow::on_Z_rotate_sliderMoved(int position)
{
    float change = (float)position * RAD;
    z_rotate_model(&ui->GL->data, &ui->GL->object, change);
    ui->GL->update();
}

void MainWindow::on_X_move_sliderMoved(int position)
{
    float change = (float)position / 10.0f;
    move_model(&ui->GL->data, &ui->GL->object, change, 0.0f, 0.0f);
    ui->GL->update();
}

void MainWindow::on_Y_move_sliderMoved(int position)
{
    float change = (float)position / 10.0f;
    move_model(&ui->GL->data, &ui->GL->object, 0.0f, change, 0.0f);
    ui->GL->update();
}

void MainWindow::on_Z_move_sliderMoved(int position)
{
    float change = (float)position / 10.0f;
    move_model(&ui->GL->data, &ui->GL->object, 0.0f, 0.0f, change);
    ui->GL->update();
}
