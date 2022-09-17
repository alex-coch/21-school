#include "s21_cat.h"

int main(int argc, char *argv[]) {
  if (argc > 1)
    cat(argc, argv);
  else
    printf("s21_cat [OPTION]... FILE...");
  return 0;
}

void init_options(Options *options) {
  options->b = 0;
  options->e = 0;
  options->E = 0;
  options->v = 0;
  options->n = 0;
  options->s = 0;
  options->t = 0;
  options->T = 0;
}

void cat(int argc, char *argv[]) {
  Options options;
  init_options(&options);
  char next_char = ' ', previous_char = '\n';

  int error = 0, i = 1, fc = 0, count_total = 0, count_nb = 0;
  for (; (i < argc) & (strspn(argv[i], "-") != 0); ++i)
    if (get_options(argv[i], &options) == 1) error = 1;
  if (options.b) options.n = 0;
  if (!error && i == argc) printf("s21_cat [OPTION]... FILE...");
  for (; !error && i < argc; ++i) {
    FILE *file_name = fopen(argv[i], "r");
    if (file_name) {
      int start_line = 1, count_empty_line = 1, count_all_line = 1;
      char ch[1024] = {'\0'};

      while ((*ch = fgetc(file_name)) != EOF) {
        if (options.s && process_s(previous_char, next_char, *ch)) continue;  //
        if (options.n) {
          if (fc) {
            fc = 0;
            if ((count_total) && (OS_LINIX) && (previous_char != '\n'))
              start_line = 0;
          }
          start_line = process_n(start_line, &count_all_line, *ch, count_total);
        }
        if (options.b) {
          if (fc) {
            fc = 0;
            if ((count_nb) && (OS_LINIX) && (previous_char != '\n'))
              start_line = 0;
          }
          start_line = process_b(start_line, previous_char, &count_empty_line,
                                 *ch, count_nb);
        }
        if (options.E) process_E(*ch);
        if (options.v) process_v(ch);
        next_char = previous_char;
        previous_char = *ch;
        if (options.T && process_T(*ch)) continue;  //
        if (*ch == '\0')
          fputc(*ch, stdout);
        else
          fputs(ch, stdout);
        memset(ch, '\0', 1024);
      }
      fclose(file_name);
      fc = 1;
      count_total = count_total + count_all_line - 1;
      count_nb = count_nb + count_empty_line - 1;
    } else {
      printf("s21_cat: %s: No such file or directory\n", argv[i]);
    }
  }
  if (error)
    printf(
        "s21_cat: invalid option -- '%s'.\nTry 'man cat' for more information.",
        argv[i - 1]);
}

int process_b(int start_line, char previous_char, int *count_empty_line,
              char ch, int count_nb) {
  if (start_line) {
    if (previous_char == '\n' && ch != '\n') {
      if (OS_LINIX) {
        printf("%6d\t", count_nb + (*count_empty_line)++);
      } else {
        printf("%6d\t", (*count_empty_line)++);
      }
    }
  }
  return ch == '\n';
}

int process_v(char *ch) {
  int current_symbol = *ch;
  if (current_symbol < 0) current_symbol += 256;
  if ((current_symbol >= 0x00 && current_symbol < 0x09) ||
      (current_symbol > 0x0A && current_symbol <= 0x1F)) {
    printf("^");
    current_symbol += 64;
  }
  if (current_symbol == 0x7F) {
    printf("^");
    current_symbol = '?';
  }
  if (current_symbol >= 128 && current_symbol <= 159) {
    printf("M-^");
    current_symbol -= 64;
  }
  if (current_symbol >= 160 && current_symbol <= 255) {
    printf("M-");
    current_symbol -= 128;
  }
  *ch = current_symbol;
  return *ch;
}

int process_E(char ch) {
  if (ch == '\n') printf("$");
  return ch == '\n';
}

int process_n(int start_line, int *count_all_line, char ch, int count_total) {
  if (start_line) {
    if (OS_LINIX) {
      printf("%6d\t", count_total + (*count_all_line)++);
    } else {
      printf("%6d\t", (*count_all_line)++);
    }
  }
  return ch == '\n';
}

int process_s(char previous_char, char next_char, char ch) {
  return ch == '\n' && previous_char == '\n' && next_char == '\n';
}

int process_T(char ch) {
  int tab = 0;
  if (ch == '\t') tab = printf("^I");
  return tab;
}

int get_options(char *argv, Options *options) {
  int error = 0;
  if (strlen(argv) == 1 || strlen(argv) != strspn(argv, "-bvEnsTet")) error = 1;
  if ((!strcmp(argv, "--number"))) {
    error = 0;
    options->n = 1;
  } else if (!strcmp(argv, "--number-nonblank")) {
    error = 0;
    options->b = 1;
  } else if (!strcmp(argv, "--squeeze-blank")) {
    error = 0;
    options->s = 1;
  } else {
    if (strchr(argv, 'b')) options->b = 1;
    if (strchr(argv, 'e')) {
      options->v = 1;
      options->E = 1;
    }
    if (strchr(argv, 'E')) options->E = 1;
    if (strchr(argv, 'v')) options->v = 1;
    if (strchr(argv, 'n')) options->n = 1;
    if (strchr(argv, 's')) options->s = 1;
    if (strchr(argv, 't')) {
      options->v = 1;
      options->T = 1;
    }
    if (strchr(argv, 'T')) options->T = 1;
  }
  return error;
}
