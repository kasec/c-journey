#include<stdio.h>
#include<stdlib.h>
#include"token.h"

struct token {
    enum Token type;
    char * lexeme;
    char * literal;
    int line;
};

struct token * Token_create(enum Token type, char * lexeme, char * literal, int line) {
    struct token *tok = malloc(sizeof (struct token));

    tok->type = type;
    tok->lexeme = lexeme;
    tok->literal = literal;
    tok->line = line;

    return tok;
}

void Token_destroy(struct token *tok) {
    free(tok);
}

void Token_print(struct token *tok) {
    printf("Token {\n type: %d,\n lexeme: %s, \n, literal: %s,\n line: %d  } \n", tok->type, tok->lexeme, tok->literal, tok->type);
}