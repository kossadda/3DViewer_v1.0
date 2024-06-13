/**
 * @file tests.c
 * @author kossadda (https://github.com/kossadda)
 * @brief
 * @version 1.0
 * @date 2024-02-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./main_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count);
static void conclusion(int passed_count, int failed_count, double time);
static void function_declaration(char *function);
static int test_suite(Suite *test, int *passed_count);
static void line();
static void declare_line(int mode);

/**
 * @brief Function to start testing modules.
 *
 * @return int - error code.
 * @retval EXIT_SUCCESS = 0 - if the tests pass successfully.
 * @retval EXIT_FAILURE = 1 - if the tests pass unsuccessful.
 */
int main(void) {
  int failed_count = 0;
  int passed_count = 0;

  struct timeval start, end;

  gettimeofday(&start, NULL);

#ifdef PARSE_ON
  Suite *(*parse[])(void) = {
      parse_test,
  };
  test_function(parse, sizeof(parse) / sizeof(parse[0]),
                "PARSE", &passed_count, &failed_count);
#endif

  gettimeofday(&end, NULL);
  double micros = (((double)((end.tv_sec - start.tv_sec) * 1000000.0) +
                    (double)end.tv_usec) -
                   (double)(start.tv_usec)) /
                  1000000.0;
  conclusion(passed_count, failed_count, micros);

  return (failed_count) ? EXIT_FAILURE : EXIT_SUCCESS;
}

/**
 * @brief Function for testing the specified Suite.
 *
 * @param[out] test input Suite test.
 * @param[out] passed_count counter of successfully passed tests.
 *
 * @return int - error code.
 * @retval EXIT_SUCCESS = 0 - if the tests pass successfully.
 * @retval EXIT_FAILURE = 1 - if the tests pass unsuccessful.
 */
static int test_suite(Suite *test, int *passed_count) {
  SRunner *suite_runner = srunner_create(test);

  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  *passed_count += srunner_ntests_run(suite_runner) - failed_count;
  srunner_free(suite_runner);

  return failed_count;
}

/**
 * @brief Collects all functions for testing into a single block.
 *
 * @param array array of function under test.
 * @param size array size.
 * @param name name of the function being tested.
 * @param passed_count number of tests passed.
 * @param failed_count number of failed tests.
 */
static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count) {
  function_declaration(name);
  for (size_t i = 0; i < size; i++) {
    line();
    *failed_count += test_suite(array[i](), passed_count);
  }
  line();
}

/**
 * @brief Prints function declaration message.
 *
 * @param[in] function name of testing function.
 */
static void function_declaration(char *function) {
  char space[] =
      "                                                                        "
      " ";
  char space1[100];
  char space2[100];
  sprintf(space1, "%s", space);
  sprintf(space2, "%s", space);
  int len = strlen(function) / 2;
  space1[strlen(space1) - len] = '\0';
  space2[strlen(space2) - (len + ((strlen(function) % 2) ? 1 : 0))] = '\0';
  declare_line(0);
  printf("|%s%s TESTS %s|\n", space1, function, space2);
  declare_line(1);
}

/**
 * @brief Prints the dividing line.
 */
static void line() {
  printf(ORANGE
         "====================================================================="
         "====================================================================="
         "=================\n");
}

static void declare_line(int mode) {
  if (mode) {
    printf("|");
  } else {
    printf(ORANGE "\n\n ");
  }
  for (int i = 0; i < 153; i++) {
    printf("_");
  }
  if (mode) {
    printf("|\n\n\n" RESET);
  } else {
    printf("\n");
  }
  if (!mode) {
    printf("|");
    for (int i = 0; i < 153; i++) {
      printf(" ");
    }
    printf("|\n");
  }
}

/**
 * @brief Prints test results.
 *
 * @param[in] passed_count number of tests passed.
 * @param[in] failed_count number of failed tests.
 */
static void conclusion(int passed_count, int failed_count, double time) {
  char result[] =
      "                                                               ";
  char temp[50];
  sprintf(temp, "%d", passed_count);
  result[strlen(result) - strlen(temp)] = '\0';
  sprintf(temp, "%d", failed_count);
  result[strlen(result) - strlen(temp)] = '\0';
  sprintf(temp, "%.2lf", time);
  result[strlen(result) - strlen(temp)] = '\0';

  printf(ORANGE
         "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
      "TOTAL RESULTS "
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~\n\n");
  printf("%sPASSED %d tests from %d for %.2lf seconds\n\n", result,
         passed_count, passed_count + failed_count, time);
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~" RESET "\n\n");
}
