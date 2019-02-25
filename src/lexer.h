#pragma once

#include <string>
#include <unordered_map>
#include <vector>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
            tok_eof = -1,

            // commands
            tok_def = -2,
            tok_extern = -3,

            // primary
            tok_identifier = -4,
            tok_number = -5,
};

static std::unordered_map<std::string, Token> token_map =
  {{"def", tok_def},
   {"extern", tok_extern}};

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

    return tok_identifier;
  }

  // Number: [0-9.]+
  if (isdigit(current_char) || current_char == '.') {
    std::string num;
    do {
      num += current_char;
      current_char = next_char();
    } while (isdigit(current_char) || current_char == '.');

    NumVal = strtod(num.c_str(), nullptr);
    return tok_number;
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
    return tok_eof;
  }

  // Otherwise, just return the character as its ascii value.
  int previous_char = current_char;
  current_char = next_char();
  return previous_char;
}
