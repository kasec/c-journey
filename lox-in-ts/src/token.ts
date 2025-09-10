export enum TokenType { // Single-character tokens.
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
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
  
    EOF
}

export type Token = {
    type: TokenType,
    lexeme: string,
    literal: string | null,
    line: number
}

export const create_token = (type: TokenType, lexeme: string, literal: null | string, line: number) => {
    return {
        type,
        lexeme,
        literal,
        line
    }
}

export const print_token = (token: Token) => {
    return `${token.type} ${token.lexeme} ${token.literal}`
}