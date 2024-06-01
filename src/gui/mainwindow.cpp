#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSlide(ui->eyeX);
    initSlide(ui->eyeY);
    initSlide(ui->eyeZ);
    initSlide(ui->centerX);
    initSlide(ui->centerY);
    initSlide(ui->centerZ);
    initSlide(ui->upX);
    initSlide(ui->upY);
    initSlide(ui->upZ);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slideSlot(int value)
{
//    if(QObject::sender() == ui->eyeX)
//        ui->GL->camera[0] = (float)ui->eyeX->value() / 1000;
//    else if(QObject::sender() == ui->eyeY)
//        ui->GL->camera[1] = (float)ui->eyeY->value() / 1000;
//    else if(QObject::sender() == ui->eyeZ)
//        ui->GL->camera[2] = (float)ui->eyeZ->value() / 1000;
//    else if(QObject::sender() == ui->centerX)
//        ui->GL->camera[3] = (float)ui->centerX->value() / 1000;
//    else if(QObject::sender() == ui->centerY)
//        ui->GL->camera[4] = (float)ui->centerY->value() / 1000;
//    else if(QObject::sender() == ui->centerZ)
//        ui->GL->camera[5] = (float)ui->centerZ->value() / 1000;
//    else if(QObject::sender() == ui->upX)
//        ui->GL->camera[6] = (float)ui->upX->value() / 1000;
//    else if(QObject::sender() == ui->upY)
//        ui->GL->camera[7] = (float)ui->upY->value() / 1000;
//    else if(QObject::sender() == ui->upZ)
//        ui->GL->camera[8] = (float)ui->upZ->value() / 1000;
//    ui->GL->update();
}

void MainWindow::initSlide(QSlider *sl) {
    sl->setMaximum(100000);
    sl->setMinimum(-100000);
    sl->setValue(0);
    connect(sl, SIGNAL(sliderMoved(int)), this, SLOT(slideSlot(int)));
}

void MainWindow::on_x_plus_clicked()
{
    move_model(&ui->GL->data, 1, 0, 0);
    ui->GL->update();
}

void MainWindow::on_x_minus_clicked()
{
    move_model(&ui->GL->data, -1, 0, 0);
    ui->GL->update();
}

void MainWindow::on_y_plus_clicked()
{
    move_model(&ui->GL->data, 0, 1, 0);
    ui->GL->update();
}

void MainWindow::on_y_minus_clicked()
{
    move_model(&ui->GL->data, 0, -1, 0);
    ui->GL->update();
}


void MainWindow::on_z_plus_clicked()
{
    move_model(&ui->GL->data, 0, 0, 1);
    ui->GL->update();
}


void MainWindow::on_z_minus_clicked()
{
    move_model(&ui->GL->data, 0, 0, -1);
    ui->GL->update();
}

