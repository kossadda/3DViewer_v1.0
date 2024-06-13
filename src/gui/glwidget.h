/**
 * @file glwidget.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header class GLWidget
 * @version 1.0
 * @date 2024-06-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QDebug>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>
#include <QButtonGroup>

extern "C" {
#include "./../modules/include/common.h"
}

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void initBuffers();
    void destroyBuffers();
    void afinneGPU(float *values);
    void initModel(QString filepath);
    void updateBuffer(float *update_to);
    void transformToIdentity();
    void setupProjection(int w, int h);
    int createImage(QString filePath, QString format);
    data_t data;
    data_t object;
    afinne_t mx;
    QColor clr_back;
    QColor clr_vert;
    QColor clr_line;
    int points;
    int pointsSize;
    int dottedLine;
    int lineSize;
    int rotationMode;
    int calculationMode;
    float sliders[7];
    int projection;
    
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
    int coeffMatrixLoc = 0;
    int colorLoc = 0;
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
