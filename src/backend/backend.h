//
// Created by valero on 12/18/23.
//

#ifndef C8_3DVIEWER_V1_0_1_BACKEND_H
#define C8_3DVIEWER_V1_0_1_BACKEND_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// #include <bits/types/FILE.h>
#include <float.h>
#include <string.h>

#include "validation.h"

#define SIZE 256

typedef struct {
  int amount_vertex;
  double *coord;
  double minMax_x[2];  // minMax[0] = min, minMax[1] = max
  double minMax_y[2];
  double minMax_z[2];
} Vertex;

typedef struct {
  int *poly;  // индексы вершин для этого полигона
  int amount_face;  // кол-во граней в одной полигоне
} Polygons;

typedef struct {
  double *max_coord;
  Vertex *v;
  Polygons *p;
  int amount_poly;  // кол-во всех полигонов
} data_t;

int parsing_file(data_t *data, const char *file_name);
int parse_string(char *string_file, data_t *data);
void apply_v(data_t *data, char *tmp, int *flag);
void apply_p(data_t *data, char *tmp, int *flag);
data_t *data_create();
void remove_data(data_t *data);
void apply_minMax(data_t *data);

void s21_array_minmax(data_t *data, double *max_coord);

#endif  // C8_3DVIEWER_V1_0_1_BACKEND_H
