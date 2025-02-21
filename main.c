#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nil 0

#define err(s, ...) do {          \
        printf(s, ##__VA_ARGS__); \
        exit(1);                  \
    } while (0)

char buf[256];

void shift_argv(int *argc, char ***argv_ptr) {
    (*argc)--;
    (*argv_ptr)++;
}

int is_str_natural_num(char *str) {
    for (char *c_ptr = str; *c_ptr != nil; *c_ptr++)
        if ('0' > *c_ptr || *c_ptr > '9')
            return 0;
    return 1;
}

int get_num_separation(int *argc, char **argv) {
    if (*argc > 1) {
        (*argc)--;
        char *arg = argv[*argc];
        if (!is_str_natural_num(arg))
            err("The last argumet must be a natural number. It denotes how digit will be separated.");
        return atoi(arg);
    }
    return 3;
}

char * get_separated_num_as_str(char *num, int sep) {
    char *ptr = buf+254;
    int count = 0;
    for (char *num_ptr = num+strlen(num)-1; num_ptr >= num; num_ptr--) {
        *ptr = *num_ptr;
        ptr--;
        count++;
        if (count % sep == 0 && num_ptr != num) {
            *ptr = ' ';
            ptr--;
        }
    }
    return ptr + 1;
}

int main(int argc, char **argv) {
    shift_argv(&argc, &argv);
    int sep = get_num_separation(&argc, argv);
    for (int i = 0; i < argc; i++) {
        char *arg = argv[i];
        if (!is_str_natural_num(arg))
            continue;
        printf("%s\n", get_separated_num_as_str(arg, sep));
    }
    return 0;
}
