import { error_log } from ".";
import { create_token, Token, TokenType } from "./token";

let source: string = ''
let tokens: Array<Token> = []

let start;
let current = 0;
let line = 0;

const keywords = new Map()
keywords.set('and', TokenType.AND);
keywords.set('class', TokenType.CLASS);
keywords.set('else', TokenType.ELSE);
keywords.set('false', TokenType.FALSE);
keywords.set('for', TokenType.FOR);
keywords.set('fun', TokenType.FUN);
keywords.set('if', TokenType.IF);
keywords.set('nil', TokenType.NIL);
keywords.set('or', TokenType.OR);
keywords.set('print', TokenType.PRINT); 
keywords.set('return', TokenType.RETURN); 
keywords.set('super', TokenType.SUPER); 
keywords.set('this', TokenType.THIS); 
keywords.set('true', TokenType.TRUE); 
keywords.set('var', TokenType.VAR); 
keywords.set('while', TokenType.WHILE); 

const isAtEnd = () => {
    return current >= source.length;
}

export function initializeScanner(_source: string) {
    source = _source;
}
// scan source code and return tokens array
export function scanTokens() {
    while(!isAtEnd()) {
        start = current
        scanToken()
    }
    
    tokens.push(create_token(TokenType.EOF, "", null, line));

    return { tokens }
}

function scanToken() {
    let c = advance();
    
    switch(c) {
        case '(': addToken(TokenType.LEFT_PAREN); break;
        case ')': addToken(TokenType.RIGHT_PAREN); break;
        case '{': addToken(TokenType.LEFT_BRACE); break;
        case '}': addToken(TokenType.RIGHT_BRACE); break;
        case ',': addToken(TokenType.COMMA); break;
        case '.': addToken(TokenType.DOT); break;
        case '-': addToken(TokenType.MINUS); break;
        case '+': addToken(TokenType.PLUS); break;
        case ';': addToken(TokenType.SEMICOLON); break;
        case '*': addToken(TokenType.STAR); break;
        case '!': addToken(match('=') ? TokenType.BANG_EQUAL : TokenType.BANG); break;
        case '=': addToken(match('=') ? TokenType.EQUAL_EQUAL : TokenType.EQUAL); break;
        case '<': addToken(match('=') ?TokenType.LESS_EQUAL : TokenType.LESS); break;
        case '*': addToken(match('=') ? TokenType.GREATER_EQUAL: TokenType.GREATER); break;
        case '/': 
            if(match('/')) {
                while(peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType.SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            // ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '"': string(); break
        case 'o':
            if(match('r')) {
                addToken(TokenType.OR);
            }
            break;
        default:
            if(isDigit(c)) {
                number();
            } else if(isAlpha(c)) {
                identifier();
            } else {
                error_log(line, "Unexpected character.");
            }
            break;
    }
}

function identifier() {
    while(isAlphaNumeric(peek())) advance();
    
    const text = source.substring(start, current);
    let type: TokenType = keywords.get(text)
    
    if (!type) type = TokenType.IDENTIFIER

    addToken(type);

}
function isAlpha(character: string) {
    return character.length === 1 && character.match(/[a-z]/i);
}
function isAlphaNumeric(character: string) {
    return isAlpha(character) && isDigit(character);
}
function isDigit(character: string) {
    const value = parseInt(character);

    return value >= 0 && value <= 9
}

function number() {
    while (isDigit(peek())) advance();

    // look for a fractional part.
    if(peek() == '.' && isDigit(peekNext())) {
        advance();
        
        while(isDigit(peek())) advance();
    }

    addToken(TokenType.NUMBER, source.substring(start, current));
}

function peekNext() {
    if (current + 1 > source.length) return '\0';
    
    return source.charAt(current++);
}

function string() {
    while(peek() != '"' && !isAtEnd()) {
        if (peek() === '\n') line ++;
        
        advance();
    }
    if (isAtEnd()) {
        error_log(line, "Unterminated string.");
    }

    // closing "
    const value = source.substring(start + 1, current - 1);
    addToken(TokenType.STRING, value)
}

function match(expected: string) {
    if (isAtEnd()) return false;
    if (source.charAt(current) != expected) return false;

    current++
    return true;
}
function peek() {
    if (isAtEnd()) return '\0';
    return source.charAt(current);
}
function advance() {
    // is this the best way to do it in js?
    return source.charAt(current++)
}

function addToken(type: TokenType, literal: null | string = null) {
    const text = source.substring(start, current);

    tokens.push(create_token(type, text, literal, line))
}