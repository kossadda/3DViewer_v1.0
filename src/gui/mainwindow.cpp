#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , leftMouse(false)
    , rightMouse(false)
{
    QIcon icon(":icon.png");
    this->setWindowIcon(icon);
    ui->setupUi(this);

    connect(ui->GL, &GLWidget::mousePress, this, &MainWindow::slotMousePress);
    connect(ui->GL, &GLWidget::mouseMove, this, &MainWindow::slotMouseMove);
    connect(ui->GL, &GLWidget::mouseWheel, this, &MainWindow::slotMouseWheel);

    QButtonGroup *group1 = new QButtonGroup(ui->other_frame);
    QButtonGroup *group2 = new QButtonGroup(ui->other_frame);
    group1->addButton(ui->calc_cpu);
    group1->addButton(ui->calc_gpu);
    ui->calc_cpu->setChecked(1);
    group2->addButton(ui->central);
    group2->addButton(ui->parallel);
    ui->central->setChecked(1);

    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Zoom_valueChanged(int position)
{
    ui->edit_scale->setValue(position);
    ui->GL->mx.scale[0] = ui->GL->mx.scale[5] = ui->GL->mx.scale[10] = (float)(position + 100.0f) / 100.0f;
    ui->GL->sliders[6] = ui->GL->mx.scale[0];

    update_vertex();
}

void MainWindow::on_X_rotate_valueChanged(int position)
{
    ui->edit_xr->setValue(position);
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_x[5] = ui->GL->mx.rotate_x[10] = std::cos(rt);
    ui->GL->mx.rotate_x[9] = std::sin(rt);
    ui->GL->mx.rotate_x[6] = -ui->GL->mx.rotate_x[9];
    ui->GL->sliders[0] = position;

    update_vertex();
}

void MainWindow::on_Y_rotate_valueChanged(int position)
{
    ui->edit_yr->setValue(position);
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_y[0] = ui->GL->mx.rotate_y[10] = std::cos(rt);
    ui->GL->mx.rotate_y[2] = std::sin(rt);
    ui->GL->mx.rotate_y[8] = -ui->GL->mx.rotate_y[2];
    ui->GL->sliders[1] = position;

    update_vertex();
}

void MainWindow::on_Z_rotate_valueChanged(int position)
{
    ui->edit_zr->setValue(position);
    float rt = (float)position * RAD;
    ui->GL->mx.rotate_z[0] = ui->GL->mx.rotate_z[5] = std::cos(rt);
    ui->GL->mx.rotate_z[4] = std::sin(rt);
    ui->GL->mx.rotate_z[1] = -ui->GL->mx.rotate_z[4];
    ui->GL->sliders[2] = position;

    update_vertex();
}

void MainWindow::on_X_move_valueChanged(int position)
{
    ui->edit_xtr->setValue(position);
    ui->GL->mx.move[3] = (float)position / 60.0f;
    ui->GL->sliders[3] = ui->GL->mx.move[3];

    update_vertex();
}

void MainWindow::on_Y_move_valueChanged(int position)
{
    ui->edit_ytr->setValue(position);
    ui->GL->mx.move[7] = (float)position / 60.0f;
    ui->GL->sliders[4] = ui->GL->mx.move[7];

    update_vertex();
}

void MainWindow::on_Z_move_valueChanged(int position)
{
    ui->edit_ztr->setValue(position);
    ui->GL->mx.move[11] = (float)position / 60.0f;
    ui->GL->sliders[5] = ui->GL->mx.move[11];

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
    ui->edit_xtr->setValue(0);
    ui->edit_ytr->setValue(0);
    ui->edit_ztr->setValue(0);
    ui->edit_xr->setValue(0);
    ui->edit_yr->setValue(0);
    ui->edit_zr->setValue(0);
    ui->edit_scale->setValue(0);

    ui->GL->clr_back = QColor(25, 20, 40);
    ui->GL->clr_vert = QColor(0, 255, 255);
    ui->GL->clr_line = QColor(255, 0, 100);
    ui->GL->points = 0;
    ui->GL->points_size = 1;
    ui->GL->dotted_line = 1;
    ui->GL->line_size = 1;
    ui->GL->calculation_mode = 0;
    ui->GL->projection = 0;

    setFrontSettings();
    update_vertex();
}

void MainWindow::update_vertex() {
    if(ui->GL->calculation_mode == 0) {
        transform_mx(&ui->GL->mx, check_sliders(), ui->GL->rotation_mode);
        mx_mult(ui->GL->data.vertexes.matrix, ui->GL->object.vertexes.matrix, ui->GL->mx.current, ui->GL->data.vertex_count);
    }

    ui->GL->update();
}

void MainWindow::slotMousePress(QMouseEvent *event) {
    startPos = event->pos();
    if (event->button() == Qt::LeftButton) {
        leftMouse = true;
        rightMouse = false;
    } else if (event->button() == Qt::RightButton) {
        leftMouse = false;
        rightMouse = true;
    } else {
        leftMouse = false;
        rightMouse = false;
    }
}

void MainWindow::slotMouseMove(QMouseEvent *event) {
    bool shiftPressed = (event->modifiers() & Qt::ShiftModifier) != 0;

    if (leftMouse) {
        QPoint offset = event->pos() - startPos;
        if(shiftPressed) {
               ui->X_move->setValue(ui->X_move->value() + (offset.x() / 2));
            ui->Y_move->setValue(ui->Y_move->value() - (offset.y() / 2));
        } else {  
            if(std::abs(ui->X_rotate->value()) == 360) ui->X_rotate->setValue(0);
            if(std::abs(ui->Y_rotate->value()) == 360) ui->Y_rotate->setValue(0);
            ui->X_rotate->setValue(ui->X_rotate->value() + (offset.y() / 2));
            ui->Y_rotate->setValue(ui->Y_rotate->value() + (offset.x() / 2));
        }
        startPos = event->pos();
    } else if (rightMouse){
        QPoint offset = event->pos() - startPos;
        if(shiftPressed) {
            ui->X_move->setValue(ui->X_move->value() + (offset.x() / 2));
            ui->Z_move->setValue(ui->Z_move->value() + (offset.y() / 2));
        } else {
            if(std::abs(ui->Y_rotate->value()) == 360) ui->Y_rotate->setValue(0);
            if(std::abs(ui->Z_rotate->value()) == 360) ui->Z_rotate->setValue(0);
            ui->Y_rotate->setValue(ui->Y_rotate->value() - (offset.x() / 2));
            ui->Z_rotate->setValue(ui->Z_rotate->value() - (offset.y() / 2));
        }
        startPos = event->pos();
    }
}

void MainWindow::slotMouseWheel(QWheelEvent *event) {
    ui->Zoom->setValue(ui->Zoom->value() + ((event->angleDelta().y() > 0) ? 10 : -10));
}

void MainWindow::on_reset_rotate_clicked()
{
    ui->X_rotate->setValue(0);
    ui->Y_rotate->setValue(0);
    ui->Z_rotate->setValue(0);
    ui->edit_xr->setValue(0);
    ui->edit_yr->setValue(0);
    ui->edit_zr->setValue(0);

    update_vertex();
}

void MainWindow::on_reset_scale_clicked()
{
    ui->Zoom->setValue(0);
    ui->edit_scale->setValue(0);

    update_vertex();
}

void MainWindow::on_reset_move_clicked()
{
    ui->X_move->setValue(0);
    ui->Y_move->setValue(0);
    ui->Z_move->setValue(0);
    ui->GL->mx.move[3] = ui->GL->mx.move[7] = ui->GL->mx.move[11] = 0.0f;
    ui->edit_xtr->setValue(0);
    ui->edit_ytr->setValue(0);
    ui->edit_ztr->setValue(0);

    update_vertex();
}

void MainWindow::on_edit_xr_valueChanged(int arg1)
{
    ui->X_rotate->setValue(arg1);
}

void MainWindow::on_edit_yr_valueChanged(int arg1)
{
    ui->Y_rotate->setValue(arg1);
}

void MainWindow::on_edit_zr_valueChanged(int arg1)
{
    ui->Z_rotate->setValue(arg1);
}

void MainWindow::on_edit_scale_valueChanged(int arg1)
{
    ui->Zoom->setValue(arg1);
}

void MainWindow::on_edit_xtr_valueChanged(int arg1)
{
    ui->X_move->setValue(arg1);
}

void MainWindow::on_edit_ytr_valueChanged(int arg1)
{
    ui->Y_move->setValue(arg1);
}

void MainWindow::on_edit_ztr_valueChanged(int arg1)
{
    ui->Z_move->setValue(arg1);
}

void MainWindow::on_back_color_clicked()
{
    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(ui->GL->clr_back);

    if (colorDialog.exec() == QDialog::Accepted) {
        ui->GL->clr_back = colorDialog.selectedColor();
    }

    ui->back_color->setStyleSheet("background-color:" + ui->GL->clr_back.name() + ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

    ui->GL->update();
}

void MainWindow::on_vertex_color_clicked()
{
    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(ui->GL->clr_vert);

    if (colorDialog.exec() == QDialog::Accepted) {
        ui->GL->clr_vert = colorDialog.selectedColor();
    }

    ui->vertex_color->setStyleSheet("background-color:" + ui->GL->clr_vert.name() + ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

    ui->GL->update();
}


void MainWindow::on_lines_color_clicked()
{
    QColorDialog colorDialog(this);

    colorDialog.setCurrentColor(ui->GL->clr_line);

    if (colorDialog.exec() == QDialog::Accepted) {
        ui->GL->clr_line = colorDialog.selectedColor();
    }

    ui->lines_color->setStyleSheet("background-color:" + ui->GL->clr_line.name() + ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

    ui->GL->update();
}

void MainWindow::on_square_points_toggled(bool checked)
{
    if(checked == true) {
        ui->GL->points = 1;
    }

    ui->GL->update();
}

void MainWindow::on_circle_points_toggled(bool checked)
{
    if(checked == true) {
        ui->GL->points = 2;
    }

    ui->GL->update();
}

void MainWindow::on_no_points_toggled(bool checked)
{
    if(checked == true) {
        ui->GL->points = 0;
    }

    ui->GL->update();
}

void MainWindow::on_point_size_valueChanged(int arg1)
{
    ui->GL->points_size = arg1;

    if(ui->GL->points != 0) {
        ui->GL->update();
    }
}

void MainWindow::on_dotted_line_toggled(bool checked)
{
    ui->GL->dotted_line = 2;
    ui->GL->update();
}

void MainWindow::on_default_line_toggled(bool checked)
{
    ui->GL->dotted_line = 1;
    ui->GL->update();
}

void MainWindow::on_no_lines_clicked()
{
    ui->GL->dotted_line = 0;
    ui->GL->update();
}

void MainWindow::on_line_size_edit_valueChanged(int arg1)
{
    ui->GL->line_size = arg1;

    if(ui->GL->dotted_line != 0) {
        ui->GL->update();
    }
}

void MainWindow::on_rotate_model_toggled(bool checked)
{
    if(checked) {
        ui->GL->rotation_mode = 0;
    }
}

void MainWindow::on_rotate_axes_toggled(bool checked)
{
    if(checked) {
        ui->GL->rotation_mode = 1;
    }
}

void MainWindow::on_load_file_clicked()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Choose wavefront obj file", QDir::homePath() + "/data-samples", "Wafefront obj (*.obj)");
    if(!openFileName.isEmpty()) {
        ui->filename->setText(openFileName);
        on_filename_returnPressed();
    }
}

void MainWindow::on_filename_returnPressed()
{
    QFileInfo fileInfo(ui->filename->text());
    if (!fileInfo.isAbsolute()) {
        QMessageBox::warning(this, "Error", "Enter the full path to the file");
    } else if(!fileInfo.exists()) {
        QMessageBox::warning(this, "Error", "File " + fileInfo.fileName() + " does not exist");
    } else if(fileInfo.suffix() != "obj") {
        QMessageBox::warning(this, "Error", "Enter path to obj file");
    } else {
        ui->GL->initModel(fileInfo.absoluteFilePath());
        ui->info_model->setText("Verticies: " + QString::number(ui->GL->data.vertex_count) + "\nFacets: " + QString::number(ui->GL->data.facet_count));
        on_reset_rotate_clicked();
        on_reset_move_clicked();
        on_reset_scale_clicked();
    }
}

void MainWindow::on_calc_cpu_toggled(bool checked)
{
    if(checked) {
        ui->GL->transformToIdentity();
        ui->GL->calculation_mode = 0;
        update_vertex();
    }
}

void MainWindow::on_calc_gpu_toggled(bool checked)
{
    if(checked) {
        ui->GL->calculation_mode = 1;
        ui->GL->update();
    }
}

void MainWindow::on_central_toggled(bool checked)
{
    if(checked) {
        ui->GL->projection = 0;
        ui->GL->setupProjection(0, 0);
        ui->GL->update();
    }
}

void MainWindow::on_parallel_toggled(bool checked)
{
    if(checked) {
        ui->GL->projection = 1;
        ui->GL->setupProjection(0, 0);
        ui->GL->update();
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::saveSettings() {
    QSettings settings("3DViewer", "3DViewerApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("back_color", ui->GL->clr_back);
    settings.setValue("vertex_color", ui->GL->clr_vert);
    settings.setValue("line_color", ui->GL->clr_line);
    settings.setValue("points", ui->GL->points);
    settings.setValue("point_size", ui->GL->points_size);
    settings.setValue("lines", ui->GL->dotted_line);
    settings.setValue("line_size", ui->GL->line_size);
    settings.setValue("calc_mode", ui->GL->calculation_mode);
    settings.setValue("projection", ui->GL->projection);
    settings.setValue("filename", ui->filename->text());
}

void MainWindow::setFrontSettings() {
    ui->back_color->setStyleSheet("border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);background-color: " + ui->GL->clr_back.name() +  ";");
    ui->vertex_color->setStyleSheet("border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);background-color: " + ui->GL->clr_vert.name() +  ";");
    ui->lines_color->setStyleSheet("border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);background-color: " + ui->GL->clr_line.name() +  ";");

    if(ui->GL->points == 0) {
        ui->no_points->setChecked(1);
    } else if(ui->GL->points == 1) {
        ui->square_points->setChecked(1);
    } else {
        ui->circle_points->setChecked(1);
    }

    if(ui->GL->dotted_line == 0) {
        ui->no_lines->setChecked(1);
    } else if(ui->GL->dotted_line == 1) {
        ui->default_line->setChecked(1);
    } else {
        ui->dotted_line->setChecked(1);
    }

    if(ui->GL->calculation_mode == 0) {
        ui->calc_cpu->setChecked(1);
    } else {
        ui->calc_gpu->setChecked(1);
    }

    if(ui->GL->projection == 0) {
        ui->central->setChecked(1);
    } else {
        ui->parallel->setChecked(1);
    }

    ui->point_size->setValue(ui->GL->points_size);
    ui->line_size_edit->setValue(ui->GL->line_size);

}

void MainWindow::loadSettings() {
    QSettings settings("3DViewer", "3DViewerApp");

    if (settings.contains("geometry")) {
        restoreGeometry(settings.value("geometry").toByteArray());
        ui->GL->clr_back = settings.value("back_color").value<QColor>();
        ui->GL->clr_vert = settings.value("vertex_color").value<QColor>();
        ui->GL->clr_line = settings.value("line_color").value<QColor>();
        ui->GL->points = settings.value("points").value<int>();
        ui->GL->points_size = settings.value("point_size").value<int>();
        ui->GL->dotted_line = settings.value("lines").value<int>();
        ui->GL->line_size = settings.value("line_size").value<int>();
        ui->GL->calculation_mode = settings.value("calc_mode").value<int>();
        ui->GL->projection = settings.value("projection").value<int>();
        ui->filename->setText(settings.value("filename").value<QString>());
    }

    setFrontSettings();
    ui->GL->update();
}

void MainWindow::on_save_image_clicked()
{
    QStringList filters("BMP Files (*.bmp)");
    filters << "JPEG Files (*.jpeg)";

    QFileDialog dialog(this, "Save image as");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setNameFilters(filters);

    if (dialog.exec() == QDialog::Accepted) {
        QString filePath = dialog.selectedFiles().first();
        QString selectedFilter = dialog.selectedNameFilter();

        QString format;
        if (selectedFilter == "BMP Files (*.bmp)") {
            format = "BMP";
            if (!filePath.endsWith(".bmp", Qt::CaseInsensitive)) {
                filePath += ".bmp";
            }
        } else {
            format = "JPEG";
            if (!filePath.endsWith(".jpeg", Qt::CaseInsensitive)) {
                filePath += ".jpeg";
            }
        }

        if (!filePath.isEmpty()) {
            ui->GL->makeCurrent();

            QImage image = ui->GL->grabFramebuffer();
            if (!image.save(filePath, format.toStdString().c_str())) {
                qWarning() << "Failed to save image";
            } else {
                qDebug() << "Image saved successfully";
            }

            ui->GL->doneCurrent();
        }
    }
}
