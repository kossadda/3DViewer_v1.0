#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_program(nullptr)
    , mx(init_afinne())
    , clr_back(25, 20, 40)
    , clr_vert(0, 255, 255)
    , clr_line(255, 0, 100)
    , points(0)
    , points_size(1)
    , dotted_line(1)
    , line_size(1)
    , rotation_mode(0)
    , calculation_mode(0)
    , projection(0)
{
    setlocale(LC_NUMERIC, "C");
    data = parse(NULL);
    object = copy_data(&data);
    std::fill(std::begin(sliders), std::end(sliders), 0.0f);
    sliders[6] = 1.0f;
}

GLWidget::~GLWidget()
{
    remove_data(&data);
    remove_data(&object);
    destroy_affine(&mx);
    destroyBuffers();
}

void GLWidget::destroyBuffers() {
    makeCurrent();
    if(vao.isCreated()) {
      vao.destroy();
    }
    if(vbo.isCreated()) {
      vbo.destroy();
    }
    if(ebo.isCreated()) {
      ebo.destroy();
    }
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
    
    glEnable(GL_DEPTH_TEST);

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
}

void GLWidget::initBuffers() {
    makeCurrent();

    if(vao.isCreated() == false) {
      vao.create();
      vao.bind();

      if(vbo.isCreated() == false) {
        vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        vbo.create();
        vbo.bind();
        vbo.setUsagePattern(QOpenGLBuffer::DynamicDraw);
        if(data.vertex_count != 0) {
            vbo.allocate(data.vertexes.matrix, data.vertex_count * 3 * sizeof(GLfloat));
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
            glEnableVertexAttribArray(0);
        }
      }

      if(ebo.isCreated() == false) {
        ebo = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        ebo.create();
        ebo.bind();
        ebo.setUsagePattern(QOpenGLBuffer::StaticDraw);
        if(data.facet_count != 0) {
            ebo.allocate(data.facets, data.full_cnt * sizeof(GLuint));
        }
      }

      vao.release();
    }
}

void GLWidget::resizeGL(int w, int h) {
    setupProjection(w, h);
}

void GLWidget::setupProjection(int w, int h) {
    if (w < 1 || h < 1) {
        w = width();
        h = height();
    }

    transformToIdentity();
    cameraMatrix.setToIdentity();
    projectionMatrix.setToIdentity();

    if(projection == 0) {
        cameraMatrix.translate(0.0f, 0.0f, -3.0f);
        projectionMatrix.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
    } else {
        float top, bottom, right, left;
        float aspect = (GLfloat)w / h;
        float coeff = 1.3f;

        if (w > h) {
            top = coeff;
            bottom = -coeff;
            right = coeff * aspect;
            left = -right;
        } else {
            right = coeff;
            left = -coeff;
            top = coeff / aspect;
            bottom = -top;
        }

        cameraMatrix.ortho(left, right, bottom, top, -100.0f, 100.0f);
    }
}

void GLWidget::afinneGPU(float *values) {
    transformToIdentity();

    rotateMatrix.rotate(values[0], 1, 0, 0);
    rotateMatrix.rotate(values[1], 0, 1, 0);
    rotateMatrix.rotate(values[2], 0, 0, 1);

    moveMatrix.translate(values[3], 0, 0);
    moveMatrix.translate(0, values[4], 0);
    moveMatrix.translate(0, 0, values[5]);

    scaleMatrix.scale(values[6], values[6], values[6]);
}

void GLWidget::transformToIdentity() {
    rotateMatrix.setToIdentity();
    moveMatrix.setToIdentity();
    scaleMatrix.setToIdentity();
}

void GLWidget::updateBuffer(float *update_to) {
    vbo.bind();
    vbo.write(0, update_to, data.vertex_count * 3 * sizeof(GLfloat));
    vbo.release();
}

void GLWidget::paintGL() {
    glClearColor(clr_back.redF(), clr_back.greenF(), clr_back.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(calculation_mode == 1) {
      updateBuffer(object.vertexes.matrix);
      afinneGPU(sliders);
    } else {
      updateBuffer(data.vertexes.matrix);
    }

    m_program->setUniformValue(m_coeffMatrixLoc, projectionMatrix * cameraMatrix * moveMatrix * rotateMatrix * scaleMatrix);

    if(vao.isCreated() && vbo.isCreated() && ebo.isCreated()) {
        vao.bind();

        if(dotted_line != 0) {
            m_program->setUniformValue("color", QVector4D(clr_line.redF(), clr_line.greenF(), clr_line.blueF(), clr_line.alphaF()));
            glLineWidth(line_size);

            if(dotted_line == 2) {
                glEnable(GL_LINE_STIPPLE);
                glLineStipple(1, 0x00FF);
            } else {
                glDisable(GL_LINE_STIPPLE);
            }

            glDrawElements(GL_LINES, data.full_cnt, GL_UNSIGNED_INT, nullptr);
        }

        if(points != 0) {
            m_program->setUniformValue("color", QVector4D(clr_vert.redF(), clr_vert.greenF(), clr_vert.blueF(), clr_vert.alphaF()));
            glPointSize(points_size);

            if(points == 2) {
                glEnable(GL_POINT_SMOOTH);
            } else {
                glDisable(GL_POINT_SMOOTH);
            }

            glDrawArrays(GL_POINTS, 0, data.vertex_count);
        }

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

void GLWidget::initModel(QString filepath) {
    std::string str = filepath.toStdString();
    remove_data(&data);
    remove_data(&object);
    data = parse((char *)str.c_str());
    normalize_vertex(&data);
    object = copy_data(&data);
    destroyBuffers();
    initBuffers();
    update();
}

void GLWidget::createImage(QString filePath, QString format) {
    makeCurrent();

    QImage image = grabFramebuffer();
    if (!image.save(filePath, format.toStdString().c_str())) {

    } else {

    }

    doneCurrent();
}
