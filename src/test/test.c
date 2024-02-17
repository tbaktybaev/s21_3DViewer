//
// Created by valero on 1/8/24.
//
#include <check.h>
#include <math.h>

#include "../backend/affin.h"
#include "../backend/backend.h"

START_TEST(test_parsing_file_1) {
  data_t *data = data_create();
  char model_file_name[] = "../data-samples/test.obj";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(data->v->amount_vertex, 8);
  ck_assert_int_eq(data->amount_poly, 12);
  remove_data(data);
}
END_TEST

START_TEST(test_parsing_file_2) {
  data_t *data = data_create();
  char *model_file_name = "../data-samples/bison_pose.obj";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 1);
  remove_data(data);
}
END_TEST

START_TEST(test_parsing_file_3) {
  data_t *data = data_create();
  char model_file_name[] = "../data-samples/Wolf.obj";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(data->v->amount_vertex, 1690);
  ck_assert_int_eq(data->amount_poly, 1566);

  remove_data(data);
}
END_TEST

START_TEST(test_parsing_file_4) {
  data_t *data = data_create();
  char model_file_name[] = "../data-samples/nothing.obj";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 0);
  remove_data(data);
}
END_TEST

START_TEST(test_parsing_file_6) {
  data_t *data = data_create();
  char model_file_name[] = "./objFiles/davlnvd.txt";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 0);
  remove_data(data);
}
END_TEST

START_TEST(test_parsing_file_7) {
  data_t *data = data_create();
  char model_file_name[] = "../data-samples/text.txt";
  int result = parsing_file(data, model_file_name);
  ck_assert_int_eq(result, 0);
  remove_data(data);
}
END_TEST

START_TEST(test_s21_move_x_1) {
  data_t *data = data_create();
  int result = parsing_file(data, "../data-samples/cube.obj");
  ck_assert_int_eq(result, 1);
  long double prev_x = data->v->coord[0];
  s21_move_x(data, 1.0);
  ck_assert_double_eq(data->v->coord[0], prev_x + 1.0);
  remove_data(data);
}
END_TEST
START_TEST(test_s21_move_y_1) {
  data_t *data = data_create();
  int result = parsing_file(data, "../data-samples/Bison_pose.obj");
  ck_assert_int_eq(result, 1);
  long double prev_y = data->v->coord[1];
  s21_move_y(data, 1.0);
  ck_assert_double_eq(data->v->coord[1], prev_y + 1.0);
  remove_data(data);
}
END_TEST
START_TEST(test_s21_move_z_1) {
  data_t *data = data_create();
  int result = parsing_file(data, "../data-samples/Wolf.obj");
  ck_assert_int_eq(result, 1);
  long double prev_z = data->v->coord[2];
  s21_move_z(data, 1.0);
  ck_assert_double_eq(data->v->coord[2], prev_z + 1.0);
  remove_data(data);
}
END_TEST

// START_TEST(test_s21_rotate_x) {
//   data_t *data = data_create();
//   data->v->amount_vertex = 8;
//   double massiv[] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
//                      0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0,
//                      0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
//   memcpy(data->v->coord, massiv, sizeof(massiv));
//   s21_rotate_x(data, 45.0, 0.0);
//   for (int i = 0; i < (data->v->amount_vertex * 3); i += 3)
//     ck_assert_double_eq_tol(data->v->coord[i], massiv[i], 0.0001);

//   ck_assert_double_eq_tol(data->v->coord[1], 0.0, 0.0001);
//   ck_assert_double_eq_tol(data->v->coord[2], 0.0, 0.0001);
//   remove_data(data);
// }
// END_TEST

START_TEST(test_s21_rotate_y_1) {
  data_t *data = data_create();
  double angle = 1, angle_prev = 0;
  s21_rotate_y(data, angle, angle_prev);
  for (int i = 0; i < data->v->amount_vertex; i += 3) {
    long double x = data->v->coord[i];
    long double z = data->v->coord[i + 2];
    ck_assert(fabsl(x - (double)cos(angle - angle_prev)) < 0.001);
    ck_assert(fabsl(z + (double)sin(angle - angle_prev)) < 0.001);
  }
}
END_TEST

// START_TEST(test_s21_rotate_z_1) {
//   data_t *data = data_create();
//   data->v->amount_vertex = 6;
//   data->v->coord = (double *)calloc(6, sizeof(double));
//   data->v->coord[3] = 1.0;
//   data->v->coord[4] = 2.0;
//   data->v->coord[5] = 3.0;
//   s21_rotate_z(data, 45.0, 0.0);
//   // ck_assert_double_eq_tol(data->v->coord[3], -(sqrt(2) / 2), 0.0001);
//   // ck_assert_double_eq_tol(data->v->coord[4], 3 * (sqrt(2) / 2), 0.0001);
//   // ck_assert_double_eq_tol(data->v->coord[5], 3.0, 0.0001);
//   remove_data(data);
// }
// END_TEST

// START_TEST(test_s21_rotate_z_2) {
//   data_t *data = data_create();
//   data->v->amount_vertex = 6;
//   data->v->coord = (double *)calloc(6, sizeof(double));
//   data->v->coord[3] = 1.0;
//   data->v->coord[4] = 2.0;
//   data->v->coord[5] = 3.0;
//   s21_rotate_z(data, 90.0, 45.0);
//   // ck_assert_double_eq_tol(data->v->coord[3], -(sqrt(2) / 2), 0.0001);
//   // ck_assert_double_eq_tol(data->v->coord[4], 3 * (sqrt(2) / 2), 0.0001);
//   remove_data(data);
// }
// END_TEST

START_TEST(test_s21_scale_1) {
  data_t *data = data_create();
  data->v->amount_vertex = 15;
  data->v->coord = (double *)calloc(15, sizeof(double));
  data->v->coord[0] = 4;
  data->v->coord[1] = -5;
  data->v->coord[2] = 6;
  data->v->coord[3] = 7;
  data->v->coord[4] = -8;
  data->v->coord[5] = 9;
  data->v->coord[6] = 0;
  data->v->coord[7] = 1;
  data->v->coord[8] = -2;
  data->v->coord[9] = -3;
  data->v->coord[10] = 4;
  data->v->coord[11] = -5;
  s21_scale(data, 2, 1);
  double result[12] = {8, -10, 12, 14, -16, 18, 0, 2, -4, -6, 8, -10};

  ck_assert_double_eq(data->v->coord[0], result[0]);
  ck_assert_double_eq(data->v->coord[1], result[1]);
  ck_assert_double_eq(data->v->coord[2], result[2]);
  ck_assert_double_eq(data->v->coord[3], result[3]);
  ck_assert_double_eq(data->v->coord[4], result[4]);
  ck_assert_double_eq(data->v->coord[5], result[5]);
  remove_data(data);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("s21_parser");
  TCase *test_case_1 = tcase_create("s21_parser");
  SRunner *sr = srunner_create(s1);
  int wtf;
  suite_add_tcase(s1, test_case_1);

  tcase_add_test(test_case_1, test_parsing_file_1);
  tcase_add_test(test_case_1, test_parsing_file_2);
  tcase_add_test(test_case_1, test_parsing_file_3);
  tcase_add_test(test_case_1, test_parsing_file_4);
  tcase_add_test(test_case_1, test_parsing_file_6);
  tcase_add_test(test_case_1, test_parsing_file_7);

  tcase_add_test(test_case_1, test_s21_move_x_1);
  tcase_add_test(test_case_1, test_s21_move_y_1);
  tcase_add_test(test_case_1, test_s21_move_z_1);

  // tcase_add_test(test_case_1, test_s21_rotate_x);
  tcase_add_test(test_case_1, test_s21_rotate_y_1);
  // tcase_add_test(test_case_1, test_s21_rotate_z_1);
  // tcase_add_test(test_case_1, test_s21_rotate_z_2);
  tcase_add_test(test_case_1, test_s21_scale_1);

  srunner_run_all(sr, CK_ENV);
  wtf = srunner_ntests_failed(sr);

  srunner_free(sr);
  return wtf == 0 ? 0 : 1;
}