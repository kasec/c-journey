#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>

int main(int argc, char *argv[]) {
    int opt;

    int line_opt = 0;
    int word_opt = 0;
    int char_opt = 0;
    int byte_opt = 0;

    char *filename = NULL;

    while((opt = getopt(argc, argv, "clmw")) != -1) {
        switch(opt) {
            case 'c':
                byte_opt = 1;
                break;
            case 'l':
                line_opt = 1;
                break;
            case 'm':
                char_opt = 1;
                break;
            case 'w':
                word_opt = 1;
                break;
            case '?':
                printf("Unknown flag: %c \n", opt);
                return EXIT_FAILURE;
        }
    }
    for(; optind < argc; optind++) {
        if (filename != NULL) {
            printf("Too many arguments: should only have file name. \n");
            return EXIT_FAILURE;
        }
        filename = argv[optind];
    }

    int word_count = 0;
    int line_count = 0;
    int char_count = 0;
    int byte_count = 0;
    FILE *f;

    if(filename == NULL) {
        f = stdin;
    } else {
        f = fopen(filename, "r");
    }

    if(f == NULL) {
        printf("Error opening file \n");
        return EXIT_FAILURE;
    }
    setlocale(LC_CTYPE, "");

    int in_word = 0;
    wint_t c;
    
    char buff[8];

    while((c = fgetwc(f)) != WEOF) {
        if (c == '\n') line_count++;

        int s = wctomb(buff, c);

        printf("char -> %c, size %d \n", c, s);
        byte_count += s;
        char_count++;
        if (!iswspace(c)) {
            if (!in_word) {
                word_count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
    }

    if (filename == NULL) {
        filename = "";
    }

    printf("\t");

    if (byte_opt) {
        printf("%d", byte_count);
    }
    if (line_opt) {
        printf("%d", line_count);
    }
    if (word_opt) {
        printf("%d", word_count);
    }
    if (char_opt) {
        printf("%d", char_count);
    }
    if (!line_opt && !word_opt && !char_opt && !byte_opt) {
        printf("%d %d %d", line_count, word_count, char_count);
    }
    printf(" %s\n", filename);

    if (strcmp(filename, "") != 0) {
        fclose(f);
    }

    return EXIT_SUCCESS;
}