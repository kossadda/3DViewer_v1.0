#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(nullptr)
    , mx(init_afinne())
    , clr_back(0, 0, 0)
    , clr_vert(255, 0, 0)
    , clr_line(255, 0, 0)
    , points(0)
    , points_size(1)
    , dotted_line(1)
    , line_size(1)
    , rotation_mode(0)
{
    setlocale(LC_NUMERIC, "C");
    data = parse(OBJECT);
    normalize_vertex(&data);
    object = copy_data(&data);
}

GLWidget::~GLWidget()
{
    remove_data(&data);
    remove_data(&object);
    destroy_affine(&mx);

    makeCurrent();
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}

void GLWidget::initializeGL() {
    initializeOpenGLFunctions();
    const char *sh_vertex =
        "attribute vec4 vertex;\n"
        "uniform mat4 coeffMatrix;\n"
        "void main() {\n"
        "   gl_Position = coeffMatrix * vertex;\n"
        "}\n";
    const char *sh_fragment =
        "uniform vec4 color;\n"
        "void main() {\n"
        "   gl_FragColor = color;\n"
        "}\n";
    
    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, sh_vertex);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, sh_fragment);

    m_program->bindAttributeLocation("vertex", 0);
    m_program->link();
    m_program->bind();
    m_coeffMatrixLoc = m_program->uniformLocation("coeffMatrix");
    m_colorLoc = m_program->uniformLocation("color");

    rotateMatrix.setToIdentity();
    moveMatrix.setToIdentity();
    scaleMatrix.setToIdentity();

    initBuffer();
}

void GLWidget::initBuffer() {
    makeCurrent();
    vao.create();
    vao.bind();
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vbo.allocate(data.vertexes.matrix, data.vertex_count * 3 * sizeof(GLfloat));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0);

    ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    ebo.create();
    ebo.bind();
    ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
    ebo.allocate(data.facets, data.full_cnt * sizeof(GLuint));

    vao.release();
}

void GLWidget::resizeGL(int w, int h) {
  setupProjection(w, h);
}

void GLWidget::setupProjection(int w, int h) {
    if (w < 1 || h < 1) {
      w = width();
      h = height();
    }

    cameraMatrix.setToIdentity();
    projectionMatrix.setToIdentity();
    rotateMatrix.setToIdentity();
    moveMatrix.setToIdentity();
    scaleMatrix.setToIdentity();
    
    projectionMatrix.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    cameraMatrix.translate(0, 0, -3);
}


void GLWidget::paintGL() {
    glClearColor(clr_back.redF(), clr_back.greenF(), clr_back.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_program->setUniformValue(m_coeffMatrixLoc, projectionMatrix * cameraMatrix * moveMatrix * rotateMatrix * scaleMatrix);

    vbo.bind();
    vbo.write(0, data.vertexes.matrix, data.vertex_count * 3 * sizeof(GLfloat));
    vbo.release();

    if(dotted_line != 0) {
        m_program->setUniformValue("color", QVector4D(clr_line.redF(), clr_line.greenF(), clr_line.blueF(), 1.0f));
        glLineWidth(line_size);

        if(dotted_line == 2) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x0F0F);
        } else {
            glDisable(GL_LINE_STIPPLE);
        }

        vao.bind();
        glDrawElements(GL_LINES, data.full_cnt, GL_UNSIGNED_INT, nullptr);
        vao.release();
    }

    if(points != 0) {
        m_program->setUniformValue("color", QVector4D(clr_vert.redF(), clr_vert.greenF(), clr_vert.blueF(), 1.0f));
        glPointSize(points_size);

        if(points == 2) {
            glEnable(GL_POINT_SMOOTH);
        } else {
            glDisable(GL_POINT_SMOOTH);
        }

        vao.bind();
        glDrawArrays(GL_POINTS, 0, data.vertex_count);
        vao.release();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    emit mousePress(event);
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    emit mouseMove(event);
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    emit mouseWheel(event);
}
