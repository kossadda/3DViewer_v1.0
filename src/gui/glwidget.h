#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <GL/glu.h>
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>
#include <QWheelEvent>

extern "C" {
#include "./../modules/include/common.h"
}

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    data_t data;
    data_t object;
    afinne_t mx;
    void initBuffers();
    void destroyBuffers();
    void setupProjection(int w = 0, int h = 0);
    void initModel(QString filepath);
    QColor clr_back;
    QColor clr_vert;
    QColor clr_line;
    int points;
    int points_size;
    int dotted_line;
    int line_size;
    int rotation_mode;
    
signals:
    void mousePress(QMouseEvent *event);
    void mouseMove(QMouseEvent *event);
    void mouseWheel(QWheelEvent *event);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    int m_coeffMatrixLoc = 0;
    int m_colorLoc = 0;
    int m_rotation;
    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;
    QOpenGLVertexArrayObject vao;
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 cameraMatrix;
    QMatrix4x4 rotateMatrix;
    QMatrix4x4 moveMatrix;
    QMatrix4x4 scaleMatrix;
};

#endif // GLWIDGET_H
