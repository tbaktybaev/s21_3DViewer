//
// Created by valero on 12/27/23.
//

#ifndef C8_3DVIEWER_V1_0_1_AFFIN_H
#define C8_3DVIEWER_V1_0_1_AFFIN_H

#include <math.h>

#include "backend.h"

void s21_move_x(data_t *data, double move);
void s21_move_y(data_t *data, double move);
void s21_move_z(data_t *data, double move);

void s21_rotate_x(data_t *data, double angle, double angle_prev);
void s21_rotate_y(data_t *data, double angle, double angle_prev);
void s21_rotate_z(data_t *data, double angle, double angle_prev);

void s21_alignment(data_t *data);

void s21_scale(data_t *data, double scale, double scale_prev);

double s21_degres_to_radians(double angle);

#endif  // C8_3DVIEWER_V1_0_1_AFFIN_H
