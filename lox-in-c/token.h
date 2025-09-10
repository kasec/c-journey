#ifndef _token_h
#define _token_h

enum Token {
    // Single-character tokens.
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
  COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

  // One or two character tokens.
  BANG, BANG_EQUAL,
  EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL,
  LESS, LESS_EQUAL,

  // Literals.
  IDENTIFIER, STRING, NUMBER,

  // Keywords.
  AND, CLASS, ELSE, FALSY, FUN, FOR, IF, NIL, OR,
  PRINT, RETURN, SUPER, THIS, TRUTHY, VAR, WHILE,

  EnOfFile,
};

struct token * Token_create(enum Token type, char * lexeme, char * literal, int line);
void Token_print(struct token *tok);

#endif