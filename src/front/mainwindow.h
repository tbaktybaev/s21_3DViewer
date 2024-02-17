#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QApplication>
#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QOpenGLBuffer>
#include <QOpenGLWidget>
#include <QProcess>
#include <QSettings>
#include <QWidget>
#include <QtOpenGL>

#include "glwidget.h"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  bool isObjFile;
  int currentRotateX = 0;
  int currentRotateY = 0;
  int currentRotateZ = 0;
  int currentMoveX = 0;
  int currentMoveY = 0;
  int currentMoveZ = 0;
  int currentScale = 25;

 signals:
  void emitRotateObjX(double value, double currentRotateX);
  void emitRotateObjY(double value, double currentRotateY);
  void emitRotateObjZ(double value, double currentRotateZ);
  void emitMoveObjX(double move);
  void emitMoveObjY(double move);
  void emitMoveObjZ(double move);
  void emitReadObjFile(QString fileName);
  void emitWidgetColorChange(QColor color);
  void emitLineColorChange(QColor color);
  void emitVertexColorChange(QColor color);
  void emitVertexSizeChange(double value);
  void emitZoomObj(int value, int currentScale);
  void emitVertexModeChange(int mode);
  void emitLineModeChange(int mode);
  void emitLineWidthChange(double value);
  void emitProjectionChange(int mode);

 private slots:
  void on_pushButton_openFile_clicked();
  void on_pushButton_screenshot_clicked();
  void on_horizontalScrollBar_rotX_valueChanged(int value);
  void on_horizontalScrollBar_rotY_valueChanged(int value);
  void on_horizontalScrollBar_rotZ_valueChanged(int value);
  void on_spinBox_rotX_valueChanged(int value);
  void on_spinBox_rotY_valueChanged(int value);
  void on_spinBox_rotZ_valueChanged(int value);
  void on_horizontalScrollBar_moveX_valueChanged(int value);
  void on_horizontalScrollBar_moveY_valueChanged(int value);
  void on_horizontalScrollBar_moveZ_valueChanged(int value);
  void on_spinBox_moveX_valueChanged(int value);
  void on_spinBox_moveY_valueChanged(int value);
  void on_spinBox_moveZ_valueChanged(int value);
  void on_horizontalSlider_VertexSize_valueChanged(int value);
  void on_pushButton_LineColor_clicked();
  void on_pushButton_BackColor_clicked();
  void on_pushButton_VertexColor_clicked();
  void on_doubleSpinBox_VertexSize_valueChanged(double arg1);
  void on_horizontalSlider_scale_valueChanged(int value);

  void on_pushButton_screencast_clicked();
  void make_gif();

  void on_radioButton_VertexCircle_toggled(bool checked);
  void on_radioButton_VertexNone_toggled(bool checked);
  void on_radioButton_VertexSquare_toggled(bool checked);
  void on_radioButton_LineDashed_toggled(bool checked);
  void on_radioButton_LineSolid_toggled(bool checked);
  void on_horizontalSlider_LineSize_valueChanged(int value);
  void on_doubleSpinBox_LineSize_valueChanged(double value);
  void on_radioButton_Parallel_toggled(bool checked);
  void on_radioButton_Central_toggled(bool checked);

 private:
  Ui::MainWindow *ui;
  QSettings *settings;

  void changeWindowColors(QColor color, int type);
  void displayObjInfo(QString filePath);
  void initSettings();
  void saveSettings();
  void downloadSettings();

  QString gif_name;
  QGifImage *gif_frame;
  int frames_counter = 0;
  QTimer *timer;
};
#endif  // MAINWINDOW_H
