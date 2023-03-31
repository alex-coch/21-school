#include <check.h>

#include "../calc.h"
#include "../pars.h"
#include "calc_suite.h"
#include "utils_suite.h"

int main(void) {
  int number_failed;
  Suite *suite;
  SRunner *suite_runner;

  number_failed = 0;

  // printf("\nCheking utils...\n");
  suite = utils_suite();
  suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);

  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  // printf("\nCheking calc...\n");

  suite = calc_suite();
  suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  number_failed += srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("Total number failures: %d\n\n", number_failed);
  return 0;
}
