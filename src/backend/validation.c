//
// Created by valero on 12/20/23.
//

#include "validation.h"

int isValidString_v(const char *str) {
  int flag = 1;
  // Проверка начинается ли строка с символа 'v'
  if (str[0] != 'v') {
    flag = 0;
    return flag;
  }
  // Переход к координатам после 'v'
  str++;

  double x, y, z;
  int numScanned = 0;
  // Попытка преобразования координат
  numScanned = sscanf(str, "%lf %lf %lf", &x, &y, &z);

  // Проверка успешности преобразования
  if (numScanned != 3) {
    flag = 0;
    return flag;
  }

  // Строка валидна
  return flag;
}

int isValidString_p(const char *str) {
  int slash = 0;
  char *tmp = strdup(str);
  int i = 0;
  if (tmp[i] == 'f') {
    i++;
    char *token = strtok(tmp + i, " ");
    while ((*token >= '0' && *token <= '9') || *token == '.' || *token == 'e' ||
           *token == '+' || *token == '-') {
      token++;
    }
    while (*token == '/') {
      slash++;
      token++;
    }
    free(tmp);
    return slash;
  }
  free(tmp);
  return slash;
}
