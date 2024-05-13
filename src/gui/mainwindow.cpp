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

void MainWindow::on_eyeXplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[0] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_eyeXminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[0] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_eyeYplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[1] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_eyeYminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[1] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_eyeZplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[2] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_eyeZminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[2] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerXplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[3] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerXminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[3] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerYplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[4] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerYminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[4] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerZplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[5] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_centerZminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[5] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_upXplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[6] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_upXminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[6] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_upYplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[7] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_upYminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[7] -= 0.25f;
    ui->GL->update();
}


void MainWindow::on_upZplus_clicked()
{
    float *camera = ui->GL->camera;
    camera[8] += 0.25f;
    ui->GL->update();
}


void MainWindow::on_upZminus_clicked()
{
    float *camera = ui->GL->camera;
    camera[8] -= 0.25f;
    ui->GL->update();
}

