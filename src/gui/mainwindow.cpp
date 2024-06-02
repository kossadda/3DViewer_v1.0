#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QIcon icon(":icon.png");
    this->setWindowIcon(icon);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Zoom_sliderMoved(int position)
{
    ui->edit_scale->setText(QString::number(position));
    ui->GL->mx.scale[0] = ui->GL->mx.scale[5] = ui->GL->mx.scale[10] = (float)(position + 100.0f) / 100.0f;

    update_vertex();
}

void MainWindow::on_X_rotate_sliderMoved(int position)
{
    ui->edit_xr->setText(QString::number(position));
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_x[5] = ui->GL->mx.rotate_x[10] = std::cos(rt);
    ui->GL->mx.rotate_x[9] = std::sin(rt);
    ui->GL->mx.rotate_x[6] = -ui->GL->mx.rotate_x[9];

    update_vertex();
}

void MainWindow::on_Y_rotate_sliderMoved(int position)
{
    ui->edit_yr->setText(QString::number(position));
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_y[0] = ui->GL->mx.rotate_y[10] = std::cos(rt);
    ui->GL->mx.rotate_y[2] = std::sin(rt);
    ui->GL->mx.rotate_y[8] = -ui->GL->mx.rotate_y[2];

    update_vertex();
}

void MainWindow::on_Z_rotate_sliderMoved(int position)
{
    ui->edit_zr->setText(QString::number(position));
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_z[0] = ui->GL->mx.rotate_z[5] = std::cos(rt);
    ui->GL->mx.rotate_z[4] = std::sin(rt);
    ui->GL->mx.rotate_z[1] = -ui->GL->mx.rotate_z[4];

    update_vertex();
}

void MainWindow::on_X_move_sliderMoved(int position)
{
    ui->edit_xtr->setText(QString::number(position));
    ui->GL->mx.move[3] = (float)position / 10.0f;

    update_vertex();
}

void MainWindow::on_Y_move_sliderMoved(int position)
{
    ui->edit_ytr->setText(QString::number(position));
    ui->GL->mx.move[7] = (float)position / 10.0f;

    update_vertex();
}

void MainWindow::on_Z_move_sliderMoved(int position)
{
    ui->edit_ztr->setText(QString::number(position));
    ui->GL->mx.move[11] = (float)position / 10.0f;

    update_vertex();
}

unsigned int MainWindow::check_sliders() {
    unsigned int res = 0;

    if(ui->X_rotate->value() != 0) {
        res |= ROTATE_X;
    }

    if(ui->Y_rotate->value() != 0) {
        res |= ROTATE_Y;
    }

    if(ui->Z_rotate->value() != 0) {
        res |= ROTATE_Z;
    }

    if(ui->X_move->value() != 0 || ui->Y_move->value() != 0 || ui->Z_move->value() != 0) {
        res |= MOVE;
    }

    if(ui->Zoom->value() != 0) {
        res |= SCALE;
    }

    return res;
}

void MainWindow::on_reset_clicked()
{
    ui->X_move->setValue(0);
    ui->Y_move->setValue(0);
    ui->Z_move->setValue(0);
    ui->X_rotate->setValue(0);
    ui->Y_rotate->setValue(0);
    ui->Z_rotate->setValue(0);
    ui->Zoom->setValue(0);
    ui->GL->mx.move[3] = ui->GL->mx.move[7] = ui->GL->mx.move[11] = 0.0f;


    ui->edit_xtr->setText("0");
    ui->edit_ytr->setText("0");
    ui->edit_ztr->setText("0");
    ui->edit_xr->setText("0");
    ui->edit_yr->setText("0");
    ui->edit_zr->setText("0");
    ui->edit_scale->setText("0");

    transform_mx(&ui->GL->mx, check_sliders());
    mx_mult(ui->GL->data.vertexes.matrix, ui->GL->object.vertexes.matrix, ui->GL->mx.current, ui->GL->data.vertex_count);
    ui->GL->update();
}

void MainWindow::update_vertex() {
    transform_mx(&ui->GL->mx, check_sliders());
    mx_mult(ui->GL->data.vertexes.matrix, ui->GL->object.vertexes.matrix, ui->GL->mx.current, ui->GL->data.vertex_count);
    ui->GL->update();
}

