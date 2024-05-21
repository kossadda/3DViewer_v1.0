#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , data(parse("/home/kossadda/desktop/3DViewer_v1.0/src/_objfiles/in cube 2.obj"))
    , m_program(nullptr)
{

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

    initBuffer();
}

void GLWidget::initBuffer() {
    makeCurrent();
    vao.create();
    vao.bind();
    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::StaticDraw);
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

void GLWidget::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.translate(0.0f, 0.0f, -10.0f);
    modelViewMatrix.rotate(m_rotation, 0.0f, 1.0f, 0.0f);
    QMatrix4x4 mvpMatrix = projectionMatrix * modelViewMatrix;
    m_program->setUniformValue("coeffMatrix", mvpMatrix);

    m_program->setUniformValue("color", QVector4D(1.0f, 0.0f, 0.0f, 1.0f));

    vao.bind();
    glDrawElements(GL_LINES, data.full_cnt, GL_UNSIGNED_INT, nullptr);
    vao.release();
    // vao.bind();
    // glDrawArrays(GL_POINTS, 0, data.vertex_count);
    // vao.release();
}

void GLWidget::setupProjection(int w, int h) {
    if (w < 1 || h < 1) {
        w = width();
        h = height();
    }

    cameraMatrix.setToIdentity();
    projectionMatrix.setToIdentity();
    
    projectionMatrix.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    cameraMatrix.translate(0, 0, -4);
}