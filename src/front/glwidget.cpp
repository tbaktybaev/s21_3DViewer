#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); };

GLWidget::~GLWidget() { remove_data(Data); }

void GLWidget::initSettings() {
  projectionMode = 0;
  vertexSize = 5;
  vertexMode = 1;
  lineWidth = 1;
  lineMode = 0;
  backgroundColor.setRgb(0, 0, 0);
  lineColor.setRgb(255, 255, 255);
  vertexColor.setRgb(255, 255, 255);
}

void GLWidget::initializeGL() {
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);  // Установка точки опоры
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  if (Data != nullptr) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScaled(0.5, 0.5, 0.5);
    glTranslatef(0, 0, -1);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    ProjectionMode();
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, Data->v->coord);
    pointHandler();
    lineHandler();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void GLWidget::lineHandler() {
  glLineWidth(lineWidth);
  glColor3d(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  if (lineMode == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }
  for (int i = 0; i < Data->amount_poly; i++) {
    glDrawElements(GL_LINES, (Data->p[i].amount_face + 1) * 2, GL_UNSIGNED_INT,
                   Data->p[i].poly);
  }
  if (lineMode == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::pointHandler() {
  if (vertexMode != 0) {
    glColor3d(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glPointSize(vertexSize);
    if (vertexMode == 1) {
      glEnable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, 0, Data->v->amount_vertex);
    if (vertexMode == 1) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}

void GLWidget::ProjectionMode() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projectionMode == 0) {
    glOrtho(-1.5, 1.5, -1.5, 1.5, -2, 1000);
  } else {
    glFrustum(-1, 1, -1, 1, 1, 99999);
    glTranslatef(0, 0, -2.8);
  }
}

void GLWidget::setProjectionMode(int mode) {
  projectionMode = mode;
  update();
}

void GLWidget::readObjFile(QString fileName) {
  QByteArray inputBytes = fileName.toUtf8();
  char *convertedFileName = strdup(inputBytes.constData());

  if (Data != nullptr) {
    remove_data(Data);
  }
  Data = data_create();
  parsing_file(Data, convertedFileName);
  std::cout << "число вершин " << Data->v->amount_vertex;
  //    apply_minMax(Data);
  free(convertedFileName);
  label_vertex = Data->v->amount_vertex;
  label_polygons = Data->amount_poly;
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  mPos = event->position();
  mLastRotX = xRot;
  mLastRotY = yRot;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  yRot = mLastRotY + event->position().x() - mPos.x();
  xRot = mLastRotX + event->position().y() - mPos.y();

  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
  mLastRotX = xRot;
  mLastRotY = yRot;
  mPos = event->position();
}

void GLWidget::rotateObjX(double value, double currentRotateX) {
  if (Data != nullptr) {
    s21_rotate_x(Data, (long double)value, (long double)currentRotateX);
    update();
  }
}

void GLWidget::rotateObjY(double value, double currentRotateY) {
  if (Data != nullptr) {
    s21_rotate_y(Data, (long double)value, (long double)currentRotateY);
    update();
  }
}

void GLWidget::rotateObjZ(double value, double currentRotateZ) {
  if (Data != nullptr) {
    s21_rotate_z(Data, (long double)value, (long double)currentRotateZ);
    update();
  }
}

void GLWidget::setScale(int value, int currentScale) {
  if (Data != nullptr) {
    s21_scale(Data, (long double)value, (long double)currentScale);
    update();
  }
}

void GLWidget::moveObjX(double move) {
  if (Data != nullptr) {
    s21_move_x(Data, move);
    update();
  }
}
void GLWidget::moveObjY(double move) {
  if (Data != nullptr) {
    s21_move_y(Data, move);
    update();
  }
}
void GLWidget::moveObjZ(double move) {
  if (Data != nullptr) {
    s21_move_z(Data, move);
    update();
  }
}

void GLWidget::setBackgroundColor(QColor color) {
  backgroundColor = color;
  update();
}
void GLWidget::setLineColor(QColor color) {
  lineColor = color;
  update();
}

void GLWidget::setVertexColor(QColor color) {
  vertexColor = color;
  update();
}

void GLWidget::setVertexSize(double value) {
  vertexSize = value;
  update();
}

void GLWidget::setVertexMode(int mode) {
  vertexMode = mode;
  update();
}

void GLWidget::setLineMode(int mode) {
  lineMode = mode;
  update();
}

void GLWidget::setLineWidth(double value) {
  lineWidth = value;
  update();
}
