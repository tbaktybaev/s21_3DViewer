//
// Created by valero on 12/27/23.
//
#include "affin.h"

void s21_move_x(data_t *data, double move) {
  for (int i = 0; data->v->coord && i < (data->v->amount_vertex) * 3; i += 3) {
    data->v->coord[i] += move;
  }
}

void s21_move_y(data_t *data, double move) {
  for (int i = 1; data->v->coord && i < data->v->amount_vertex * 3; i += 3) {
    data->v->coord[i] += move;
  }
}

void s21_move_z(data_t *data, double move) {
  for (int i = 2; data->v->coord && i < data->v->amount_vertex * 3; i += 3) {
    data->v->coord[i] += move;
  }
}

void s21_rotate_x(data_t *data, double angle, double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0; data->v->coord && i < data->v->amount_vertex * 3; i += 3) {
    double y = data->v->coord[i + 1];
    double z = data->v->coord[i + 2];

    data->v->coord[i + 1] =
        y * cos(angle - angle_prev) + z * sin(angle - angle_prev);
    data->v->coord[i + 2] =
        -y * sin(angle - angle_prev) + z * cos(angle - angle_prev);
  }
}

void s21_rotate_y(data_t *data, double angle, double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0; data->v->coord && i < data->v->amount_vertex * 3; i += 3) {
    double x = data->v->coord[i];
    double z = data->v->coord[i + 2];
    data->v->coord[i] =
        x * cos(angle - angle_prev) + z * sin(angle - angle_prev);
    data->v->coord[i + 2] =
        -x * sin(angle - angle_prev) + z * cos(angle - angle_prev);
  }
}

void s21_rotate_z(data_t *data, double angle, double angle_prev) {
  angle = s21_degres_to_radians(angle);
  angle_prev = s21_degres_to_radians(angle_prev);
  for (int i = 0; data->v->coord && i < data->v->amount_vertex * 3; i += 3) {
    double x = data->v->coord[i];
    double y = data->v->coord[i + 1];

    data->v->coord[i] =
        x * cos(angle - angle_prev) - y * sin(angle - angle_prev);
    data->v->coord[i + 1] =
        x * sin(angle - angle_prev) + y * cos(angle - angle_prev);
  }
}

double s21_degres_to_radians(double angle) { return angle * M_PI / 180.0; }

void s21_scale(data_t *data, double scale, double scale_prev) {
  for (int i = 0; data->v->coord && i < data->v->amount_vertex * 3; i++) {
    data->v->coord[i] *= scale / scale_prev;
  }
}

void s21_alignment(data_t *data) {
  double centerX =
      data->v->minMax_x[0] + (data->v->minMax_x[1] - data->v->minMax_x[0]) / 2;
  double centerY =
      data->v->minMax_y[0] + (data->v->minMax_y[1] - data->v->minMax_y[0]) / 2;
  double centerZ =
      data->v->minMax_z[0] + (data->v->minMax_z[1] - data->v->minMax_z[0]) / 2;
  printf("%       f %f %f\n", centerX, centerY, centerZ);

  for (int i = 0; i < data->v->amount_vertex; i += 3) {
    data->v->coord[i] -= centerX;
    data->v->coord[i + 1] -= centerY;
    data->v->coord[i + 2] -= centerZ;
  }
}
