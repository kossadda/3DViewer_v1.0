/**
 * @file viewer.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief viewer class (main program) description module
 * @version 1.0
 * @date 2024-06-13
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "viewer.h"

#include "./gif.h"
#include "./ui_viewer.h"

viewer::viewer(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::viewer),
      leftMouse(false),
      rightMouse(false),
      periodicTimer(new QTimer(this)),
      countdownTimer(new QTimer(this)),
      gifCount(0),
      gifFps(10),
      gifLength(5),
      dir(QFileInfo(QString(__FILE__)).absoluteDir()),
      screenDir(".images"),
      absScreenDir(dir.absolutePath() + QString("/") + screenDir +
                   QString("/")),
      timer(3),
      recording(false),
      loadFile(QFileDialog(this, "Choose wavefront obj file", QDir::homePath(),
                           "Wavefront obj (*.obj)")),
      saveImg(QFileDialog(this, "Save image as", QDir::homePath())),
      saveGif(QFileDialog(this, "Save gif as", QDir::homePath(),
                          "GIF Files (*.gif)")),
      colorDialog(QColorDialog(this)) {
  QIcon icon(":icon.png");
  this->setWindowIcon(icon);
  ui->setupUi(this);

  saveGif.setAcceptMode(QFileDialog::AcceptSave);
  saveImg.setAcceptMode(QFileDialog::AcceptSave);
  saveImg.setNameFilters(QStringList("BMP Files (*.bmp)")
                         << "JPEG Files (*.jpeg)");
  loadFile.setStyleSheet(
      "background-color: rgb(30, 30, 30);color: rgb(255, 255, 255)");
  saveImg.setStyleSheet(
      "background-color: rgb(30, 30, 30);color: rgb(255, 255, 255)");
  saveGif.setStyleSheet(
      "background-color: rgb(30, 30, 30);color: rgb(255, 255, 255)");
  colorDialog.setStyleSheet(
      "background-color: rgb(30, 30, 30);color: rgb(255, 255, 255)");

  connect(ui->GL, &GLWidget::mousePress, this, &viewer::slotMousePress);
  connect(ui->GL, &GLWidget::mouseMove, this, &viewer::slotMouseMove);
  connect(ui->GL, &GLWidget::mouseWheel, this, &viewer::slotMouseWheel);

  connect(periodicTimer, &QTimer::timeout, this, &viewer::createSnapshot);
  connect(countdownTimer, &QTimer::timeout, this, &viewer::countDown);

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

viewer::~viewer() { delete ui; }

void viewer::on_Zoom_valueChanged(int position) {
  ui->edit_scale->setValue(position);
  ui->GL->mx.scale[0] = ui->GL->mx.scale[5] = ui->GL->mx.scale[10] =
      (float)(position + 100.0f) / 100.0f;
  ui->GL->sliders[6] = ui->GL->mx.scale[0];

  updateVertex();
}

void viewer::on_X_rotate_valueChanged(int position) {
  ui->edit_xr->setValue(position);
  float rt = (float)position * RAD;
  ui->GL->mx.rotate_x[5] = ui->GL->mx.rotate_x[10] = std::cos(rt);
  ui->GL->mx.rotate_x[9] = std::sin(rt);
  ui->GL->mx.rotate_x[6] = -ui->GL->mx.rotate_x[9];
  ui->GL->sliders[0] = position;

  updateVertex();
}

void viewer::on_Y_rotate_valueChanged(int position) {
  ui->edit_yr->setValue(position);
  float rt = (float)position * RAD;
  ui->GL->mx.rotate_y[0] = ui->GL->mx.rotate_y[10] = std::cos(rt);
  ui->GL->mx.rotate_y[2] = std::sin(rt);
  ui->GL->mx.rotate_y[8] = -ui->GL->mx.rotate_y[2];
  ui->GL->sliders[1] = position;

  updateVertex();
}

void viewer::on_Z_rotate_valueChanged(int position) {
  ui->edit_zr->setValue(position);
  float rt = (float)position * RAD;
  ui->GL->mx.rotate_z[0] = ui->GL->mx.rotate_z[5] = std::cos(rt);
  ui->GL->mx.rotate_z[4] = std::sin(rt);
  ui->GL->mx.rotate_z[1] = -ui->GL->mx.rotate_z[4];
  ui->GL->sliders[2] = position;

  updateVertex();
}

void viewer::on_X_move_valueChanged(int position) {
  ui->edit_xtr->setValue(position);
  ui->GL->mx.move[3] = (float)position / 60.0f;
  ui->GL->sliders[3] = ui->GL->mx.move[3];

  updateVertex();
}

void viewer::on_Y_move_valueChanged(int position) {
  ui->edit_ytr->setValue(position);
  ui->GL->mx.move[7] = (float)position / 60.0f;
  ui->GL->sliders[4] = ui->GL->mx.move[7];

  updateVertex();
}

void viewer::on_Z_move_valueChanged(int position) {
  ui->edit_ztr->setValue(position);
  ui->GL->mx.move[11] = (float)position / 60.0f;
  ui->GL->sliders[5] = ui->GL->mx.move[11];

  updateVertex();
}

unsigned int viewer::check_sliders() {
  unsigned int res = 0;

  if (ui->X_rotate->value() != 0) {
    res |= ROTATE_X;
  }

  if (ui->Y_rotate->value() != 0) {
    res |= ROTATE_Y;
  }

  if (ui->Z_rotate->value() != 0) {
    res |= ROTATE_Z;
  }

  if (ui->X_move->value() != 0 || ui->Y_move->value() != 0 ||
      ui->Z_move->value() != 0) {
    res |= MOVE;
  }

  if (ui->Zoom->value() != 0) {
    res |= SCALE;
  }

  return res;
}

void viewer::on_reset_clicked() {
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
  ui->GL->clr_vert = QColor(255, 255, 0);
  ui->GL->clr_line = QColor(52, 194, 255);
  ui->GL->points = 0;
  ui->GL->pointsSize = 1;
  ui->GL->dottedLine = 1;
  ui->GL->lineSize = 1;
  ui->GL->calculationMode = 0;
  ui->GL->projection = 0;

  setFrontSettings();
  updateVertex();
}

void viewer::updateVertex() {
  if (ui->GL->calculationMode == 0) {
    transform_mx(&ui->GL->mx, check_sliders());
    mx_mult_vector(ui->GL->data.vertexes.matrix, ui->GL->object.vertexes.matrix,
                   ui->GL->mx.current, ui->GL->data.vertex_count);
  }

  ui->GL->update();
}

void viewer::slotMousePress(QMouseEvent *event) {
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

void viewer::slotMouseMove(QMouseEvent *event) {
  bool shiftPressed = (event->modifiers() & Qt::ShiftModifier) != 0;

  if (leftMouse) {
    QPoint offset = event->pos() - startPos;
    if (shiftPressed) {
      ui->X_move->setValue(ui->X_move->value() + (offset.x() / 2));
      ui->Y_move->setValue(ui->Y_move->value() - (offset.y() / 2));
    } else {
      if (std::abs(ui->X_rotate->value()) == 360) ui->X_rotate->setValue(0);
      if (std::abs(ui->Y_rotate->value()) == 360) ui->Y_rotate->setValue(0);
      ui->X_rotate->setValue(ui->X_rotate->value() + (offset.y() / 2));
      ui->Y_rotate->setValue(ui->Y_rotate->value() + (offset.x() / 2));
    }
    startPos = event->pos();
  } else if (rightMouse) {
    QPoint offset = event->pos() - startPos;
    if (shiftPressed) {
      ui->X_move->setValue(ui->X_move->value() + (offset.x() / 2));
      ui->Z_move->setValue(ui->Z_move->value() + (offset.y() / 2));
    } else {
      if (std::abs(ui->Y_rotate->value()) == 360) ui->Y_rotate->setValue(0);
      if (std::abs(ui->Z_rotate->value()) == 360) ui->Z_rotate->setValue(0);
      ui->Y_rotate->setValue(ui->Y_rotate->value() - (offset.x() / 2));
      ui->Z_rotate->setValue(ui->Z_rotate->value() - (offset.y() / 2));
    }
    startPos = event->pos();
  }
}

void viewer::slotMouseWheel(QWheelEvent *event) {
  ui->Zoom->setValue(ui->Zoom->value() +
                     ((event->angleDelta().y() > 0) ? 10 : -10));
}

void viewer::on_reset_rotate_clicked() {
  ui->X_rotate->setValue(0);
  ui->Y_rotate->setValue(0);
  ui->Z_rotate->setValue(0);
  ui->edit_xr->setValue(0);
  ui->edit_yr->setValue(0);
  ui->edit_zr->setValue(0);

  updateVertex();
}

void viewer::on_reset_scale_clicked() {
  ui->Zoom->setValue(0);
  ui->edit_scale->setValue(0);

  updateVertex();
}

void viewer::on_reset_move_clicked() {
  ui->X_move->setValue(0);
  ui->Y_move->setValue(0);
  ui->Z_move->setValue(0);
  ui->GL->mx.move[3] = ui->GL->mx.move[7] = ui->GL->mx.move[11] = 0.0f;
  ui->edit_xtr->setValue(0);
  ui->edit_ytr->setValue(0);
  ui->edit_ztr->setValue(0);

  updateVertex();
}

void viewer::on_edit_xr_valueChanged(int arg1) { ui->X_rotate->setValue(arg1); }

void viewer::on_edit_yr_valueChanged(int arg1) { ui->Y_rotate->setValue(arg1); }

void viewer::on_edit_zr_valueChanged(int arg1) { ui->Z_rotate->setValue(arg1); }

void viewer::on_edit_scale_valueChanged(int arg1) { ui->Zoom->setValue(arg1); }

void viewer::on_edit_xtr_valueChanged(int arg1) { ui->X_move->setValue(arg1); }

void viewer::on_edit_ytr_valueChanged(int arg1) { ui->Y_move->setValue(arg1); }

void viewer::on_edit_ztr_valueChanged(int arg1) { ui->Z_move->setValue(arg1); }

void viewer::on_back_color_clicked() {
  colorDialog.setCurrentColor(ui->GL->clr_back);

  if (colorDialog.exec() == QDialog::Accepted) {
    ui->GL->clr_back = colorDialog.selectedColor();
  }

  ui->back_color->setStyleSheet(
      "background-color:" + ui->GL->clr_back.name() +
      ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

  ui->GL->update();
}

void viewer::on_vertex_color_clicked() {
  colorDialog.setCurrentColor(ui->GL->clr_vert);

  if (colorDialog.exec() == QDialog::Accepted) {
    ui->GL->clr_vert = colorDialog.selectedColor();
  }

  ui->vertex_color->setStyleSheet(
      "background-color:" + ui->GL->clr_vert.name() +
      ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

  ui->GL->update();
}

void viewer::on_lines_color_clicked() {
  colorDialog.setCurrentColor(ui->GL->clr_line);

  if (colorDialog.exec() == QDialog::Accepted) {
    ui->GL->clr_line = colorDialog.selectedColor();
  }

  ui->lines_color->setStyleSheet(
      "background-color:" + ui->GL->clr_line.name() +
      ";border-radius: 17px;border: 3px solid rgba(189, 0, 195, 0.25);");

  ui->GL->update();
}

void viewer::on_square_points_toggled(bool checked) {
  if (checked == true) {
    ui->GL->points = 1;
  }

  ui->GL->update();
}

void viewer::on_circle_points_toggled(bool checked) {
  if (checked == true) {
    ui->GL->points = 2;
  }

  ui->GL->update();
}

void viewer::on_no_points_toggled(bool checked) {
  if (checked == true) {
    ui->GL->points = 0;
  }

  ui->GL->update();
}

void viewer::on_point_size_valueChanged(int arg1) {
  ui->GL->pointsSize = arg1;

  if (ui->GL->points != 0) {
    ui->GL->update();
  }
}

void viewer::on_dotted_line_toggled(bool checked) {
  ui->GL->dottedLine = 2;
  ui->GL->update();
}

void viewer::on_default_line_toggled(bool checked) {
  ui->GL->dottedLine = 1;
  ui->GL->update();
}

void viewer::on_no_lines_clicked() {
  ui->GL->dottedLine = 0;
  ui->GL->update();
}

void viewer::on_line_size_edit_valueChanged(int arg1) {
  ui->GL->lineSize = arg1;

  if (ui->GL->dottedLine != 0) {
    ui->GL->update();
  }
}

void viewer::on_load_file_clicked() {
  if (loadFile.exec() == QDialog::Accepted) {
    ui->filename->setText(loadFile.selectedFiles().first());
    on_filename_returnPressed();
  }
}

void viewer::on_filename_returnPressed() {
  QFileInfo fileInfo(ui->filename->text());
  if (!fileInfo.isAbsolute()) {
    QMessageBox::warning(this, "Error", "Enter the full path to the file");
  } else if (!fileInfo.exists()) {
    QMessageBox::warning(this, "Error",
                         "File " + fileInfo.fileName() + " does not exist");
  } else if (fileInfo.suffix() != "obj") {
    QMessageBox::warning(this, "Error", "Enter path to obj file");
  } else {
    if (!ui->GL->initModel(fileInfo.absoluteFilePath())) {
      ui->info_model->setText(
          "Verticies: " + QString::number(ui->GL->data.vertex_count) +
          "\nFacets: " + QString::number(ui->GL->data.facet_count));
      on_reset_rotate_clicked();
      on_reset_move_clicked();
      on_reset_scale_clicked();
    } else {
      QMessageBox::warning(this, "Error", "Invalid obj file");
    }
  }
}

void viewer::on_calc_cpu_toggled(bool checked) {
  if (checked) {
    ui->GL->transformToIdentity();
    ui->GL->calculationMode = 0;
    updateVertex();
  }
}

void viewer::on_calc_gpu_toggled(bool checked) {
  if (checked) {
    ui->GL->calculationMode = 1;
    ui->GL->update();
  }
}

void viewer::on_central_toggled(bool checked) {
  if (checked) {
    ui->GL->projection = 0;
    ui->GL->setupProjection(0, 0);
    ui->GL->update();
  }
}

void viewer::on_parallel_toggled(bool checked) {
  if (checked) {
    ui->GL->projection = 1;
    ui->GL->setupProjection(0, 0);
    ui->GL->update();
  }
}

void viewer::closeEvent(QCloseEvent *event) {
  saveSettings();
  QMainWindow::closeEvent(event);
}

void viewer::saveSettings() {
  QSettings settings("3DViewer", "3DViewerApp");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("back_color", ui->GL->clr_back);
  settings.setValue("vertex_color", ui->GL->clr_vert);
  settings.setValue("line_color", ui->GL->clr_line);
  settings.setValue("points", ui->GL->points);
  settings.setValue("point_size", ui->GL->pointsSize);
  settings.setValue("lines", ui->GL->dottedLine);
  settings.setValue("line_size", ui->GL->lineSize);
  settings.setValue("calc_mode", ui->GL->calculationMode);
  settings.setValue("projection", ui->GL->projection);
  settings.setValue("filename", ui->filename->text());
}

void viewer::setFrontSettings() {
  ui->back_color->setStyleSheet(
      "border-radius: 17px;border: 3px solid rgba(189, 0, 195, "
      "0.25);background-color: " +
      ui->GL->clr_back.name() + ";");
  ui->vertex_color->setStyleSheet(
      "border-radius: 17px;border: 3px solid rgba(189, 0, 195, "
      "0.25);background-color: " +
      ui->GL->clr_vert.name() + ";");
  ui->lines_color->setStyleSheet(
      "border-radius: 17px;border: 3px solid rgba(189, 0, 195, "
      "0.25);background-color: " +
      ui->GL->clr_line.name() + ";");

  if (ui->GL->points == 0) {
    ui->no_points->setChecked(1);
  } else if (ui->GL->points == 1) {
    ui->square_points->setChecked(1);
  } else {
    ui->circle_points->setChecked(1);
  }

  if (ui->GL->dottedLine == 0) {
    ui->no_lines->setChecked(1);
  } else if (ui->GL->dottedLine == 1) {
    ui->default_line->setChecked(1);
  } else {
    ui->dotted_line->setChecked(1);
  }

  if (ui->GL->calculationMode == 0) {
    ui->calc_cpu->setChecked(1);
  } else {
    ui->calc_gpu->setChecked(1);
  }

  if (ui->GL->projection == 0) {
    ui->central->setChecked(1);
  } else {
    ui->parallel->setChecked(1);
  }

  ui->point_size->setValue(ui->GL->pointsSize);
  ui->line_size_edit->setValue(ui->GL->lineSize);
}

void viewer::loadSettings() {
  QSettings settings("3DViewer", "3DViewerApp");

  if (settings.contains("geometry")) {
    restoreGeometry(settings.value("geometry").toByteArray());
    ui->GL->clr_back = settings.value("back_color").value<QColor>();
    ui->GL->clr_vert = settings.value("vertex_color").value<QColor>();
    ui->GL->clr_line = settings.value("line_color").value<QColor>();
    ui->GL->points = settings.value("points").value<int>();
    ui->GL->pointsSize = settings.value("point_size").value<int>();
    ui->GL->dottedLine = settings.value("lines").value<int>();
    ui->GL->lineSize = settings.value("line_size").value<int>();
    ui->GL->calculationMode = settings.value("calc_mode").value<int>();
    ui->GL->projection = settings.value("projection").value<int>();
    ui->filename->setText(settings.value("filename").value<QString>());
  }

  setFrontSettings();
  ui->GL->update();
}

void viewer::on_save_image_clicked() {
  if (saveImg.exec() == QDialog::Accepted) {
    QString filePath = saveImg.selectedFiles().first();
    QString selectedFilter = saveImg.selectedNameFilter();

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

    if (!filePath.isEmpty() && !ui->GL->createImage(filePath, format)) {
      QMessageBox::warning(this, "Error",
                           "Error when creating a snapshot of the model");
    }
  }
}

void viewer::on_save_gif_clicked() {
  if (recording == false) {
    recording = true;
    gifCount = 0;
    dir.mkdir(screenDir);
    timer = 3;
    countdownTimer->start(1000);
    ui->save_gif->setStyleSheet(QString(
        "QPushButton {font-weight: bold;background-color: rgba(101, 0, 189, "
        "1);color: rgb(255, 255, 255);font-size: 14px;border-radius: "
        "20px;padding: 6px 12px;border: 3px solid rgba(189, 0, 195, 0.75);} "
        "QPushButton:pressed {background-color: rgb(76, 20, 98);}"));
    ui->save_gif->setText(QString::number(timer));
  }
}

void viewer::countDown() {
  timer--;
  ui->save_gif->setText(QString::number(timer));

  if (timer == 0) {
    countdownTimer->stop();
    ui->save_gif->setText("Recording");
    periodicTimer->start(1000 / gifFps);
  }
}

void viewer::createSnapshot() {
  gifCount++;

  QString format = QString(".bmp");

  ui->GL->createImage(absScreenDir + QString::number(gifCount) + format, "BMP");

  if (gifCount == gifFps * gifLength) {
    periodicTimer->stop();

    if (saveGif.exec() == QFileDialog::Accepted) {
      QString filePath = saveGif.selectedFiles().first();
      if (!filePath.endsWith(".gif", Qt::CaseInsensitive)) {
        filePath += ".gif";
      }

      createGif(filePath);
    }

    QDir imagesDir(dir.absoluteFilePath(screenDir));
    if (imagesDir.exists()) {
      imagesDir.removeRecursively();
    }

    recording = false;
    ui->save_gif->setText("Save gif");
    ui->save_gif->setStyleSheet(QString(
        "QPushButton {font-weight: bold;background-color: rgba(101, 0, 189, "
        "0.15);color: rgb(255, 255, 255);font-size: 14px;border-radius: "
        "20px;padding: 6px 12px;border: 3px solid rgba(189, 0, 195, 0.25);} "
        "QPushButton:pressed {background-color: rgb(76, 20, 98);}"));
  }
}

void viewer::createGif(QString path_to_gif) {
  bool correct = true;

  QString format = QString(".bmp");

  GifWriter writer = {};
  if (!GifBegin(&writer, path_to_gif.toStdString().c_str(), 640, 480, gifFps)) {
    correct = false;
  }

  for (int count = 1; count <= gifFps * gifLength && correct; count++) {
    QString framePath = absScreenDir + QString::number(count) + format;
    QImage frame(framePath);

    if (frame.isNull()) {
      correct = false;
      break;
    }

    QImage convertedFrame = frame.convertToFormat(QImage::Format_RGBA8888);
    if (convertedFrame.width() != 640 || convertedFrame.height() != 480) {
      convertedFrame = convertedFrame.scaled(640, 480);
    }

    if (!GifWriteFrame(&writer, convertedFrame.bits(), 640, 480, gifFps)) {
      correct = false;
      break;
    }
  }

  GifEnd(&writer);

  if (correct == false) {
    QMessageBox::warning(this, "Error",
                         "An error occurred while recording a GIF image");
  }
}
