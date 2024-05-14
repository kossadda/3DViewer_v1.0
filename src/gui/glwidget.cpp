#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , data(parse("/home/kossadda/develop/3DViewer_v1.0/data-samples/cube.obj"))
{
    for(int i = 0; i < 9; i++) {
        if(i == 2) camera[i] = 5.0f;
        else if(i == 7) camera[i] = 1.0f;
        else camera[i] = 0.0f;
    }
}

void GLWidget::initializeGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
    glEnable(GL_DEPTH_TEST);
}


void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 1.0f, 50.0f);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera[0], camera[1], camera[2],
              camera[3], camera[4], camera[5],
              camera[6], camera[7], camera[8]);

    glPointSize(10.0f);

    for(int i = 0; i < data.facet_count; i++) {
        glBegin(GL_LINE_LOOP);
        int *ptr = data.facets[i].vertexes;
        for(int j = 0; j < data.facets[i].count; j++) {
            glVertex3f(data.vertexes.matrix[ptr[j]][0], data.vertexes.matrix[ptr[j]][1], data.vertexes.matrix[ptr[j]][2]);
        }
        glEnd();
    }
}
