#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 8192

typedef struct {
  int e;  // Pattern.
  int i;  // Ignore uppercase vs. lowercase.
  int v;  // Invert match.
  int c;  // Output count of matching lines only.
  int l;  // Output matching files only.
  int n;  // Precede each matching line with a line number.
  int h;  // Output matching lines without preceding them by file names.
  int s;  // Suppress error messages about nonexistent or unreadable files.
  int f;  // Take regexes from a file.
  int o;  // Output the matched parts of a matching line.
} Flags;

enum { SUCCESS, FILE_DOES_NOT_EXIST, FLAG_DOES_NOT_EXIST, MALLOC_ERROR };

void _grep(Flags *flags, char *file_name, char *pattern[], int count_file);

int _init_flags(Flags *flags);

int _get_flags(char *argv, Flags *flags);

void _get_files(int argc, char *argv[], Flags *flags);

int _get_count_files(char *file_name[]);

int _get_args(int argc, char *argv[], char *file_name[], char *pattern[],
              Flags *flags);

int _check_flags_exist(char *argv);

void _reset_flag_e_and_f(Flags *flags);

int _handle_flag_f(char *file_name, char *patterns[], int *index);

int _pattern_matching(const char *const linep, char *pattern[], char *matches[],
                      const Flags *flags);

void _handle_header(char *file_name, int count_file, Flags *flags);

void _handle_flag_n(int count_line, Flags *flags);

void _handle_header_flag_c(Flags *flags, char *file_name, int count_file);

void _handle_flag_c(Flags *flags, int count_matched_lines);

void _handle_flag_l(Flags *flags, char *file_name, int count_matched_lines);
#endif  // SRC_GREP_S21_GREP_H_
