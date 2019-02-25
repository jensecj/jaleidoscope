#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "token.h"

static std::unordered_map<std::string, Token::Token> token_map =
  {{"def", Token::tok_def},
   {"extern", Token::tok_extern}};

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

static int point = 0;

char next_char() {
  point += 1;
  return getchar();
}

/// Return the next token from standard input.
static int eat() {
  static int current_char = ' ';

  // Skip any whitespace.
  while (isspace(current_char)) {
    current_char = next_char();
  }

  // identifier: [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(current_char)) {
    IdentifierStr = current_char;

    while (isalnum((current_char = next_char()))) {
      IdentifierStr += current_char;
    }

    if (token_map.find(IdentifierStr) != token_map.end()) {
      return token_map[IdentifierStr];
    }

    return Token::tok_identifier;
  }

  // Number: [0-9.]+
  if (isdigit(current_char) || current_char == '.') {
    std::string num;
    do {
      num += current_char;
      current_char = next_char();
    } while (isdigit(current_char) || current_char == '.');

    NumVal = strtod(num.c_str(), nullptr);
    return Token::tok_number;
  }

  if (current_char == '#') {
    // Comment until end of line.
    do {
      current_char = next_char();
    }
    while (current_char != EOF && current_char != '\n' && current_char != '\r');

    if (current_char != EOF) {
      return eat();
    }
  }

  // Check for end of file.  Don't eat the EOF.
  if (current_char == EOF) {
    return Token::tok_eof;
  }

  // Otherwise, just return the character as its ascii value.
  int previous_char = current_char;
  current_char = next_char();
  return previous_char;
}
