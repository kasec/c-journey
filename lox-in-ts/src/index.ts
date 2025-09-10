import fs from 'node:fs';
import * as readline from 'node:readline/promises';
import { stdin as input, stdout as output } from 'node:process';

import { initializeScanner, scanTokens } from './scanner';
// Lox class in runtime in this file
const rl = readline.createInterface({ input, output });

const argv = process.argv || [];
let hadError = false;
const len = argv.length

if(len > 3) {
    console.log("Usage: jlox [script]");
    if (hadError) process.exit(64)
} else if(argv.length == 3) {
    runFile(argv[2]);
} else {
    runPrompt();
}

function runFile(pathname: string) {
    const data = fs.readFileSync('/Users/joe/test.txt', 'utf8');
    
    run(data);
    
    if (hadError) process.exit(65)
}
function run(source: string) {
    // initialize scanner with source
    initializeScanner(source);
    // scan source and return tokens
    const { tokens } = scanTokens();


    tokens.forEach((token) => {
        console.log(token)
    })
}

export function error_log(line: number, message: string) {
    report_info(line, "", message);
}
function report_info(line: number, where: string, message: string) {
    console.error(`[line ${line}] Error ${where}: ${message}`)
    hadError = true
}

async function runPrompt() {
    while(true) {
        const line = await rl.question('> ');
        
        if(!line) break;

        run(line);

        if (hadError) process.exit(65)
    }
}