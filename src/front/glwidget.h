#ifndef SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_
#define SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_

#define GL_SILENCE_DEPRECATION

#include <QMessageBox>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

extern "C" {
#include "../backend/affin.h"
#include "../backend/backend.h"
#include "../backend/validation.h"
}

#if defined(linux) || defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/GLUT.h>
#endif

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  unsigned int label_vertex = 0;
  unsigned int label_polygons = 0;
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  QColor backgroundColor;
  QColor lineColor;
  QColor vertexColor;

 public slots:
  void rotateObjX(double value, double currentRotateX);
  void rotateObjY(double value, double currentRotateY);
  void rotateObjZ(double value, double currentRotateZ);
  void moveObjX(double move);
  void moveObjY(double move);
  void moveObjZ(double move);
  void readObjFile(QString fileName);
  void setBackgroundColor(QColor color);
  void setLineColor(QColor color);
  void setVertexColor(QColor color);
  void setVertexSize(double value);
  void setScale(int value, int currentScale);
  void setVertexMode(int mode);
  void setLineMode(int mode);
  void setLineWidth(double value);
  void ProjectionMode();
  void setProjectionMode(int mode);

 private:
  data_t *Data = nullptr;

  float xRot, yRot, mLastRotY, mLastRotX;
  QPointF mPos;

  int projectionMode;
  int vertexMode;
  int vertexSize;
  int lineWidth;
  int lineMode;

  //    double max_coord = 5;

  void initSettings();
  void PerspectiveSettings();
  void pointHandler();
  void lineHandler();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif  // SRC_3DVIEWER_FRONT_OPENGL_GLWIDGET_H_
