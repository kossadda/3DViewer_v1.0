#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <GL/glu.h>
#include <QDebug>
#include <QMatrix4x4>

extern "C" {
#include "./../modules/include/common.h"
}

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    float camera[9];
    void updateCamera();
    data_t data;

protected:
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 modelViewMatrix;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
};

#endif // GLWIDGET_H
