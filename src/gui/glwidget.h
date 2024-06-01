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

extern "C" {
#include "./../modules/include/common.h"
}

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    data_t data;
    void initBuffer();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

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
};

#endif // GLWIDGET_H
