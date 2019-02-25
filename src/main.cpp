#include <iostream>
#include <string>

#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "ast.h"

static void handle_definition() {
  if (ParseDefinition()) {
    std::cerr << "Parsed a function definition." << std::endl;
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void handle_extern() {
  if (ParseExtern()) {
    std::cout << "Parsed an extern." << std::endl;
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void handle_top_level_expression() {
  // Evaluate a top-level expression into an anonymous function.
  if (ParseTopLevelExpr()) {
    std::cout << "Parsed a top-level expr." << std::endl;
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

/// top ::= definition | external | expression | ';'
static void repl() {
  while (true) {
    std::cout << "ready> ";

    switch (CurTok) {
    case Token::tok_eof:
      return;
    case ';': // ignore top-level semicolons.
      getNextToken();
      break;
    case Token::tok_def:
      handle_definition();
      break;
    case Token::tok_extern:
      handle_extern();
      break;
    default:
      handle_top_level_expression();
      break;
    }
  }
}

int main() {
  // Install standard binary operators.
  // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; // highest.

  // Prime the first token.
  std::cout << "ready> ";
  getNextToken();

  // Run the main "interpreter loop" now.
  repl();

  return 0;
}
