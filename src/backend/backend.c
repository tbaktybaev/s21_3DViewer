//
// Created by valero on 12/18/23.
//
#include "backend.h"

int parsing_file(data_t *data, const char *file_name) {
  if (!data) return 0;
  int flag = 1;
  FILE *f;
  char string_file[SIZE] = {'\0'};
  if ((f = fopen(file_name, "r")) != NULL) {
    while (flag && fgets(string_file, SIZE, f)) {
      flag = parse_string(string_file, data);
      if (flag)
        continue;
      else
        flag = 0;
    }
    if (flag) {
      apply_minMax(data);
      data->v->amount_vertex /= 3;
    }
    fclose(f);
  } else {
    flag = 0;
  }
  return flag;
}

int parse_string(char *string_file, data_t *data) {
  int flag = 1;
  char *tmp = string_file;
  if (string_file[0] == 'v' || string_file[0] == 'f') {
    if (string_file[1] == ' ') {
      char c = string_file[0];
      if (c == 'v') {
        if (!isValidString_v(string_file)) {
          flag = 0;
        } else {
          apply_v(data, tmp, &flag);
        }
      } else if (c == 'f') {
        int slash = isValidString_p(string_file);
        if (slash >= 0) {
          apply_p(data, tmp, &flag);
          if (flag == 0) {
            return 0;
          }
        } else {
          return 0;
        }
      }
    }
  }
  return flag;
}

void apply_v(data_t *data, char *tmp, int *flag) {
  size_t i = data->v->amount_vertex;
  if (data->v->coord == NULL) {
    *flag = 0;
    return;
  }
  tmp++;
  double x, y, z;
  int count = 0;
  count = sscanf(tmp, "%lf %lf %lf", &x, &y, &z);
  if (count == 3) {
    data->v->coord[i] = x;
    data->v->coord[i + 1] = y;
    data->v->coord[i + 2] = z;
  } else {
    *flag = 0;
    return;
  }
  data->v->amount_vertex += 3;
  data->v->coord =
      realloc(data->v->coord, (data->v->amount_vertex + 3) * sizeof(double));
}

void apply_p(data_t *data, char *tmp, int *flag) {
  if (data->p[data->amount_poly].poly == NULL) {
    data->p[data->amount_poly].poly = (int *)calloc(100, sizeof(int));
    data->p[data->amount_poly].amount_face = 0;
  }

  int ind_of_vert = 0;
  tmp++;
  char *token = strtok(tmp, " ");
  int count;
  int num = 0;
  while (token != NULL) {
    count = sscanf(token, "%d", &num);
    token = strtok(NULL, " ");
    if (count == 1) {
      data->p[data->amount_poly].poly[ind_of_vert] = num;
      ind_of_vert++;
    } else {
      *flag = 0;
      return;
    }
    if (ind_of_vert > 1) data->p[data->amount_poly].amount_face++;
  }
  *flag = 1;
  size_t ind = 1;

  int *mass = (int *)calloc((data->p[data->amount_poly].amount_face + 1) * 2,
                            sizeof(int));
  mass[0] = data->p[data->amount_poly].poly[0] - 1;
  size_t n = (data->p[data->amount_poly].amount_face + 1) * 2 - 1;
  for (size_t i = 1; i < n; i += 2) {
    mass[i] = data->p[data->amount_poly].poly[ind] - 1;
    if ((int)i != (data->p[data->amount_poly].amount_face + 1) * 2 - 1) {
      mass[i + 1] = data->p[data->amount_poly].poly[ind++] - 1;
    }
  }
  mass[(data->p[data->amount_poly].amount_face + 1) * 2 - 1] =
      data->p[data->amount_poly].poly[0] - 1;
  memcpy(data->p[data->amount_poly].poly, mass,
         4 * (data->p[data->amount_poly].amount_face + 1) * 2);
  free(mass);
  data->amount_poly++;
}

void apply_minMax(data_t *data) {
  if (data->v->coord) {
    double max_x = DBL_MIN;
    double min_x = DBL_MAX;
    double max_y = DBL_MIN;
    double min_y = DBL_MAX;
    double max_z = DBL_MIN;
    double min_z = DBL_MAX;
    for (int i = 0; i < data->v->amount_vertex; i += 3) {
      if (data->v->coord[i] > max_x) {
        data->v->minMax_x[1] = data->v->coord[i];
        max_x = data->v->coord[i];
      }
      if (data->v->coord[i] < min_x) {
        data->v->minMax_x[0] = data->v->coord[i];
        min_x = data->v->coord[i];
      }
      if (data->v->coord[i + 1] > max_y) {
        data->v->minMax_y[1] = data->v->coord[i + 1];
        max_y = data->v->coord[i + 1];
      }
      if (data->v->coord[i + 1] < min_y) {
        data->v->minMax_y[0] = data->v->coord[i + 1];
        min_y = data->v->coord[i + 1];
      }
      if (data->v->coord[i + 2] > max_z) {
        data->v->minMax_z[1] = data->v->coord[i + 2];
        max_z = data->v->coord[i + 2];
      }
      if (data->v->coord[i + 2] < min_z) {
        data->v->minMax_z[0] = data->v->coord[i + 2];
        min_z = data->v->coord[i + 2];
      }
    }
  }
}

data_t *data_create() {
  data_t *data = calloc(3, sizeof(data_t));
  data->v = calloc(1, sizeof(Vertex));
  data->v->minMax_x[0] = DBL_MAX;
  data->v->minMax_x[1] = DBL_MIN;
  data->v->minMax_y[0] = DBL_MAX;
  data->v->minMax_y[1] = DBL_MIN;
  data->v->minMax_z[0] = DBL_MAX;
  data->v->minMax_z[1] = DBL_MIN;
  data->v->coord = calloc(3, sizeof(double));
  data->p = calloc(10000000, sizeof(Polygons));
  return data;
}

void remove_data(data_t *data) {
  if (data != NULL) {
    for (int i = 0; i < data->amount_poly; i++) {
      if (data->p[i].poly != NULL) free(data->p[i].poly);
    }
    if (data->p != NULL) free(data->p);
    data->p = NULL;
    if (data->v->coord != NULL) free(data->v->coord);
    data->v->coord = NULL;
    if (data->v != NULL) free(data->v);
    data->v = NULL;
    if (data != NULL) free(data);
    data = NULL;
  }
}