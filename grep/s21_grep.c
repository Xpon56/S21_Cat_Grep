#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char pattern[1024];
  int len_pattern;
} arguments;

void regular_pattern(arguments* arg, char* pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_pattern_flagF(arguments* arg, char* filepatch) {
  FILE* f = fopen(filepatch, "r");
  if (f == NULL) {
    if (!arg->s) perror(filepatch);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = getline(&line, &memlen, f);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    regular_pattern(arg, line);
    read = getline(&line, &memlen, f);
  }
  free(line);
  fclose(f);
}
arguments arguments_parser(int argc, char* argv[]) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        regular_pattern(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 'f':
        arg.f = 1;
        add_pattern_flagF(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
    }
  }
  if (arg.len_pattern == 0) {
    regular_pattern(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}
void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void printf_flagO(regex_t* re, char* line) {
  regmatch_t math;
  int endwhile = 0;
  while (1) {
    int result = regexec(re, line + endwhile, 1, &math, 0);
    if (result != 0) {
      break;
    }
    for (int i = math.rm_so; i < math.rm_eo; i++) {
      putchar(line[i]);
    }
    putchar('\n');
    endwhile += math.rm_eo;
  }
}

void manipulationFile(arguments arg, char* path, int flag, regex_t* reg) {
  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char* line = NULL;
  size_t memlen = 0;
  int read = 0;
  int line_counter = 1;
  int flagC_counter = 0;
  read = getline(&line, &memlen, f);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);

    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (arg.n) printf("%d:", line_counter);
        if (arg.o) {
          printf_flagO(reg, line);
        } else {
          if (flag == 1 && !arg.h) {
            printf("%s:", path);
          }
          output_line(line, read);
        }
      }
      flagC_counter++;
    }
    read = getline(&line, &memlen, f);
    line_counter++;
  }
  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", flagC_counter);
  }
  if (arg.l && flagC_counter > 0) printf("%s\n", path);
  fclose(f);
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) perror("ERROR");
  for (int i = optind; i < argc; i++) {
    int flag = 0;
    if (argc - optind > 1) {
      flag = 1;
    }
    manipulationFile(arg, argv[i], flag, &re);
  }
  regfree(&re);
}

int main(int argc, char** argv) {
  arguments arg = arguments_parser(argc, argv);
  output(arg, argc, argv);
  return 0;
}
