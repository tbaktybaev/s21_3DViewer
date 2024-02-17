#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowTitle("3D Viewer");
  settings = new QSettings("settings.conf", QSettings::IniFormat, this);
  timer = new QTimer(this);

  connect(this, SIGNAL(emitRotateObjX(double, double)), ui->glWidget,
          SLOT(rotateObjX(double, double)));
  connect(this, SIGNAL(emitRotateObjY(double, double)), ui->glWidget,
          SLOT(rotateObjY(double, double)));
  connect(this, SIGNAL(emitRotateObjZ(double, double)), ui->glWidget,
          SLOT(rotateObjZ(double, double)));
  connect(this, SIGNAL(emitMoveObjX(double)), ui->glWidget,
          SLOT(moveObjX(double)));
  connect(this, SIGNAL(emitMoveObjY(double)), ui->glWidget,
          SLOT(moveObjY(double)));
  connect(this, SIGNAL(emitMoveObjZ(double)), ui->glWidget,
          SLOT(moveObjZ(double)));
  connect(this, SIGNAL(emitWidgetColorChange(QColor)), ui->glWidget,
          SLOT(setBackgroundColor(QColor)));
  connect(this, SIGNAL(emitLineColorChange(QColor)), ui->glWidget,
          SLOT(setLineColor(QColor)));
  connect(this, SIGNAL(emitVertexColorChange(QColor)), ui->glWidget,
          SLOT(setVertexColor(QColor)));
  connect(this, SIGNAL(emitZoomObj(int, int)), ui->glWidget,
          SLOT(setScale(int, int)));
  connect(this, SIGNAL(emitVertexModeChange(int)), ui->glWidget,
          SLOT(setVertexMode(int)));
  connect(this, SIGNAL(emitLineModeChange(int)), ui->glWidget,
          SLOT(setLineMode(int)));
  connect(this, SIGNAL(emitLineWidthChange(double)), ui->glWidget,
          SLOT(setLineWidth(double)));
  connect(this, SIGNAL(emitVertexSizeChange(double)), ui->glWidget,
          SLOT(setVertexSize(double)));
  connect(this, SIGNAL(emitReadObjFile(QString)), ui->glWidget,
          SLOT(readObjFile(QString)));
  connect(this, SIGNAL(emitProjectionChange(int)), ui->glWidget,
          SLOT(setProjectionMode(int)));
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));

  downloadSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete settings;
  delete timer;
  delete ui;
}

void MainWindow::on_pushButton_openFile_clicked() {
  QDir::setCurrent(QCoreApplication::applicationDirPath());
  QDir dir(QDir::currentPath());
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cdUp();
  dir.cd("data-samples");
  QString dataSamplesDir = dir.absolutePath();
  QString filePath = QFileDialog::getOpenFileName(
      this, "Open file", dataSamplesDir, ".obj (*.obj)");
  if (filePath.isEmpty()) {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error!");
    warning.setText("File was not chosen.");
    QPixmap pixmap(":/assets/Viewer.icns");
    warning.setIconPixmap(pixmap);
    warning.exec();
    isObjFile = 0;
  } else {
    QString fileName = QFileInfo(filePath).fileName();
    QString message = "You opened the file: " + fileName;
    QMessageBox msgBox(QMessageBox::Information, "File opened", message,
                       QMessageBox::Ok, this);
    msgBox.setWindowIcon(QIcon(":assets/Viewer.icns"));
    msgBox.exec();
    isObjFile = 1;
    emit emitReadObjFile(filePath);
    initSettings();
    displayObjInfo(filePath);
  }
}

void MainWindow::displayObjInfo(QString filePath) {
  QFileInfo fi(filePath);
  QString name = fi.fileName();
  ui->label_name->setText(name);
  ui->label_vertex->setText(QString::number(ui->glWidget->label_vertex, 10));
  ui->label_polygons->setText(
      QString::number(ui->glWidget->label_polygons, 10));
}

void MainWindow::on_pushButton_screenshot_clicked() {
  QImage img = ui->glWidget->grabFramebuffer();
  QString screenshot = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
  if (!screenshot.isNull()) {
    img.save(screenshot);
  }
}

void MainWindow::on_horizontalScrollBar_rotX_valueChanged(int value) {
  emit emitRotateObjX((double)value, (double)currentRotateX);
  currentRotateX = (double)value;
  ui->spinBox_rotX->setValue(value);
}

void MainWindow::on_spinBox_rotX_valueChanged(int value) {
  ui->horizontalScrollBar_rotX->setValue(value);
}

void MainWindow::on_horizontalScrollBar_rotY_valueChanged(int value) {
  emit emitRotateObjY((double)value, (double)currentRotateY);
  currentRotateY = (double)value;
  ui->spinBox_rotY->setValue(value);
}

void MainWindow::on_spinBox_rotY_valueChanged(int value) {
  ui->horizontalScrollBar_rotY->setValue(value);
}

void MainWindow::on_horizontalScrollBar_rotZ_valueChanged(int value) {
  emit emitRotateObjZ((double)value, (double)currentRotateZ);
  currentRotateZ = (double)value;
  ui->spinBox_rotZ->setValue(value);
}

void MainWindow::on_spinBox_rotZ_valueChanged(int value) {
  ui->horizontalScrollBar_rotZ->setValue(value);
}

void MainWindow::on_horizontalScrollBar_moveX_valueChanged(int value) {
  double moveVal = (value - currentMoveX) / 100.0;
  emit emitMoveObjX(moveVal);
  currentMoveX = value;
  ui->spinBox_moveX->setValue(value);
}

void MainWindow::on_horizontalScrollBar_moveY_valueChanged(int value) {
  double moveVal = (value - currentMoveY) / 100.0;
  emit emitMoveObjY(moveVal);
  currentMoveY = value;
  ui->spinBox_moveY->setValue(value);
}

void MainWindow::on_horizontalScrollBar_moveZ_valueChanged(int value) {
  double moveVal = (value - currentMoveZ) / 100.0;
  emit emitMoveObjZ(moveVal);
  currentMoveZ = value;
  ui->spinBox_moveZ->setValue(value);
}

void MainWindow::on_spinBox_moveX_valueChanged(int value) {
  ui->horizontalScrollBar_moveX->setValue(value);
}

void MainWindow::on_spinBox_moveY_valueChanged(int value) {
  ui->horizontalScrollBar_moveY->setValue(value);
}

void MainWindow::on_spinBox_moveZ_valueChanged(int value) {
  ui->horizontalScrollBar_moveZ->setValue(value);
}

void MainWindow::on_pushButton_BackColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    emit emitWidgetColorChange(color);
    changeWindowColors(color, 1);
  }
}

void MainWindow::on_pushButton_LineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    emit emitLineColorChange(color);
    changeWindowColors(color, 2);
  }
}

void MainWindow::on_pushButton_VertexColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
  if (color.isValid()) {
    emit emitVertexColorChange(color);
    changeWindowColors(color, 3);
  }
}

void MainWindow::changeWindowColors(QColor color, int type) {
  if (type == 1) {
    ui->label_BackColor->setAutoFillBackground(true);
    ui->label_BackColor->setStyleSheet(
        QString("border-style: solid; border-width: 1px; border-color: black; "
                "background-color: %1;")
            .arg(color.name()));
  } else if (type == 2) {
    ui->label_LineColor->setAutoFillBackground(true);
    ui->label_LineColor->setStyleSheet(
        QString("border-style: solid; border-width: 1px; border-color: black; "
                "background-color: %1;")
            .arg(color.name()));
  } else {
    ui->label_VertexColor->setAutoFillBackground(true);
    ui->label_VertexColor->setStyleSheet(
        QString("border-style: solid; border-width: 1px; border-color: black; "
                "background-color: %1;")
            .arg(color.name()));
  }
}
void MainWindow::on_horizontalSlider_VertexSize_valueChanged(int value) {
  emit emitVertexSizeChange((double)value);
  ui->doubleSpinBox_VertexSize->setValue((double)value);
}
void MainWindow::on_doubleSpinBox_VertexSize_valueChanged(double arg1) {
  emit emitVertexSizeChange(arg1);
  ui->horizontalSlider_VertexSize->setValue((int)arg1);
}

void MainWindow::on_horizontalSlider_scale_valueChanged(int value) {
  //  if (value < currentScale) {
  emit emitZoomObj(value, currentScale);
  //  } else {
  //    emit emitZoomObj(1, currentScale);
  //  }
  currentScale = value;
}

void MainWindow::on_pushButton_screencast_clicked() {
  if (isObjFile) {
    QDateTime current_date = QDateTime::currentDateTime();
    QString formattedTime = current_date.toString("yyyy-MM-dd hh.mm.ss");
    QString name_pattern = "Screen Cast " + formattedTime + ".gif";
    gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                            name_pattern, tr("gif (*.gif)"));
    if (gif_name != "") {
      ui->pushButton_screencast->setDisabled(true);
      gif_frame = new QGifImage;
      gif_frame->setDefaultDelay(10);
      timer->setInterval(100);
      timer->start();
    }
  } else {
    QMessageBox warning = QMessageBox();
    warning.setWindowTitle("Error");
    warning.setText("Please open .obj file to take a screencast");
    warning.setIcon(QMessageBox::Warning);
    warning.exec();
  }
}

void MainWindow::make_gif() {
  QImage image = ui->glWidget->grabFramebuffer();
  QSize imageSize(640, 480);
  QImage scaledImage = image.scaled(imageSize);
  gif_frame->addFrame(scaledImage);
  if (frames_counter == 50) {
    timer->stop();
    gif_frame->save(gif_name);
    frames_counter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif file saved successfully");
    delete gif_frame;
    ui->pushButton_screencast->setText("");
    ui->pushButton_screencast->setEnabled(true);
  }
  frames_counter++;
  if (!ui->pushButton_screencast->isEnabled()) {
    ui->pushButton_screencast->setText(QString::number(frames_counter / 10) +
                                       "s");
  }
  if (ui->pushButton_screencast->isEnabled()) {
    ui->pushButton_screencast->setText("Record screencast");
  }
}

void MainWindow::on_radioButton_VertexCircle_toggled(bool checked) {
  emit emitVertexModeChange(1);
}

void MainWindow::on_radioButton_VertexNone_toggled(bool checked) {
  emit emitVertexModeChange(0);
}

void MainWindow::on_radioButton_VertexSquare_toggled(bool checked) {
  emit emitVertexModeChange(2);
}

void MainWindow::on_radioButton_LineDashed_toggled(bool checked) {
  emit emitLineModeChange(1);
}

void MainWindow::on_radioButton_LineSolid_toggled(bool checked) {
  emit emitLineModeChange(0);
}

void MainWindow::on_horizontalSlider_LineSize_valueChanged(int value) {
  emit emitLineWidthChange(value);
  ui->doubleSpinBox_LineSize->setValue(value);
}

void MainWindow::on_doubleSpinBox_LineSize_valueChanged(double value) {
  emit emitLineWidthChange(value);
  ui->horizontalSlider_LineSize->setValue(value);
}

void MainWindow::on_radioButton_Parallel_toggled(bool checked) {
  emit emitProjectionChange(0);
}

void MainWindow::on_radioButton_Central_toggled(bool checked) {
  emit emitProjectionChange(1);
}
