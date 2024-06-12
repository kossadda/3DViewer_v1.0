#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include "./glwidget.h"
#include <QThread>
#include <QDir>

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
    void updateVertex();
    void on_reset_rotate_clicked();
    void on_reset_scale_clicked();
    void on_reset_move_clicked();
    void on_edit_xr_valueChanged(int arg1);
    void on_edit_yr_valueChanged(int arg1);
    void on_edit_zr_valueChanged(int arg1);
    void on_edit_scale_valueChanged(int arg1);
    void on_edit_xtr_valueChanged(int arg1);
    void on_edit_ytr_valueChanged(int arg1);
    void on_edit_ztr_valueChanged(int arg1);
    void on_back_color_clicked();
    void on_vertex_color_clicked();
    void on_lines_color_clicked();
    void on_square_points_toggled(bool checked);
    void on_circle_points_toggled(bool checked);
    void on_no_points_toggled(bool checked);
    void on_point_size_valueChanged(int arg1);
    void on_dotted_line_toggled(bool checked);
    void on_default_line_toggled(bool checked);
    void on_no_lines_clicked();
    void on_line_size_edit_valueChanged(int arg1);
    void on_rotate_model_toggled(bool checked);
    void on_rotate_axes_toggled(bool checked);
    void on_load_file_clicked();
    void on_filename_returnPressed();
    void on_calc_cpu_toggled(bool checked);
    void on_calc_gpu_toggled(bool checked);
    void on_central_toggled(bool checked);
    void on_parallel_toggled(bool checked);
    void saveSettings();
    void loadSettings();
    void setFrontSettings();
    void on_save_image_clicked();
    void on_save_gif_clicked();
    void createSnapshot();
    void createGif(QString path_to_gif);
    void countDown();
    
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPoint startPos;
    bool leftMouse;
    bool rightMouse;
    int gifCount;
    int gifFps;
    int gifLength;
    int timer;
    bool recording;
    QTimer *periodicTimer;
    QTimer *countdownTimer;
    QDir dir;
    QString screenDir;
    QString absScreenDir;

public slots:
    void slotMousePress(QMouseEvent *event);
    void slotMouseMove(QMouseEvent *event);
    void slotMouseWheel(QWheelEvent *event);
};

#endif // MAINWINDOW_H
