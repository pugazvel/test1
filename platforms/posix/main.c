#include <stdio.h>
#include <string.h>
#include "smartjs.h"

void run_file(const char *file_name) {
  v7_val_t res;
  printf("Executing %s\n", file_name);
  if (v7_exec_file(v7, &res, file_name) != V7_OK) {
    printf("%s execution: ", file_name);
    v7_println(v7, res);
  }
}

void run_expr(const char *expr) {
  v7_val_t res;
  if (v7_exec(v7, &res, expr) != V7_OK) {
    printf("Execution error [%s]:\n", expr);
    v7_println(v7, res);
  }
}

void run_startups() {
  static const char *startup_files[] = {"smart.js", "init.js"};
  int i;

  for (i = 0; i < sizeof(startup_files) / sizeof(startup_files[0]); i++) {
    run_file(startup_files[i]);
  }
}

int main(int argc, char *argv[]) {
  const char *exprs[16], *files[16];
  int i, nexprs = 0, nfiles = 0;

  for (i = 1; i < argc && argv[i][0] == '-'; i++) {
    if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      exprs[nexprs++] = argv[i + 1];
      i++;
    } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
      files[nfiles++] = argv[i + 1];
      i++;
    }
  }

  init_v7();

  run_startups();

  for (i = 0; i < nfiles; i++) {
    run_file(files[i]);
  }

  for (i = 0; i < nexprs; i++) {
    run_expr(exprs[i]);
  }

  v7_destroy(v7);

  return 0;
}
