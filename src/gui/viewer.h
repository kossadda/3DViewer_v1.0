#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Viewer; }
QT_END_NAMESPACE

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Viewer : public QOpenGLWidget
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = nullptr);
    ~Viewer();

private:
    Ui::Viewer *ui;
};
#endif // VIEWER_H
