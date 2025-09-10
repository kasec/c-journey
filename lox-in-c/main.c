#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include"token.h"
static int had_error = 0;
static int start;
static int current;
static int line;
static char source[10];

void run_file(char * path);
void run_prompt();
void run_program();
void report(int line, char * where, char * message);
char advance();
void generate_tokens();
int is_at_end();
struct token * scan_token();

int main (int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: jlox [script]");
    } else if(argc == 2) {
        run_file(argv[1]);
    } else {
        run_prompt();
    }

    return 0;
}

void run_file(char * path) {
    FILE * fptr = fopen(path, "r"); 
}

void run_prompt() {
    // improve this later
    // how can I check the size of the buffer and create the string
    // or how other compilers manage it
    while(1) {
        printf("> ");
        scanf("%s", source);
        
        printf("[LOG] run_prompt() source %s \n", source);
        run_program();
        printf("[LOG] run_prompt() had_error %d \n", had_error);
        if (had_error) exit(65);
    }

}

void error(int line, char * message) {
    report(line, "", message);
}

void report(int line, char * where, char * message) {
    printf("[line %d] Error %s : %s \n", line, where, message);
    had_error = 1;
}

void run_program() {
    generate_tokens();
}

void generate_tokens() {
    int end = is_at_end();
    printf("[LOG] generate_tokens() end? %d \n", end);
    while(end) {
        start = current;
        struct token * tok = scan_token();
        Token_print(tok);
    }
    // print eof token here, once the while loop ends up
}

struct token * scan_token() {
    char c = advance();
    printf("scan_token() - advance() -> character (%c) \n", c);

    switch (c) {
        case '(':
            return Token_create(LEFT_PAREN, &c, &c, line);
            break;
        case ')':
            return Token_create(RIGHT_PAREN, &c, &c, line);
            break;
        case '{':
            return Token_create(LEFT_BRACE, &c, &c, line);
            break;
        case '}':
            return Token_create(RIGHT_BRACE, &c, &c, line);
            break;
        case ',':
            return Token_create(COMMA, &c, &c, line);
            break;
        case '.':
            return Token_create(DOT, &c, &c, line);
            break;
        case '-':
            return Token_create(MINUS, &c, &c, line);
            break;
        case '+':
            return Token_create(PLUS, &c, &c, line);
            break;
        case ';':
            return Token_create(SEMICOLON, &c, &c, line);
            break;
        case '*':
            return Token_create(STAR, &c, &c, line);
            break;
        
        default:
            if (is_digit(c)) {
                number()
            }
            error(line, "Unexpected character");
            break;
    }
}

char peek() {
    if (is_at_end()) return '\0';

    return source[current];
}

char peek_next() {
    if (source[current + 1] == '\0') return '\0';

    return source[current + 1];
}

void number() {
    while (is_digit(peek())) advance();

    // look for a fractional part.
    if(peek() == '.' && is_digit(peek_next)) {
        advance();

        while(is_digit(peek())) advance();
    }
}

char advance() {
    // move cursor to next element
    // and return it
    current++;
    return source[current];
}

int is_at_end() {
    char c = source[current];
    printf("[LOG] is_at_end() -> character(Token<%c>) \n", c);
    // instead of do the lengt function
    // how could I check out last character,
    // I remember something with '/0', let me research more about it
    return c != '\0';
}

/*
TO-DO
- [ ] create the lexer only in a single file
- [ ] once lexer works try to move to its own files
- [ ] error handling should be in its own file
- [ ] Should I do this in golang? now that I'm working on tribu
*/
