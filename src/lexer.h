#pragma once

#include <string>

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

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

/// Return the next token from standard input.
static int eat() {
  static int current_char = ' ';

  // Skip any whitespace.
  while (isspace(current_char))
    current_char = getchar();

  if (isalpha(current_char)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = current_char;
    while (isalnum((current_char = getchar())))
      IdentifierStr += current_char;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(current_char) || current_char == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += current_char;
      current_char = getchar();
    } while (isdigit(current_char) || current_char == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return tok_number;
  }

  if (current_char == '#') {
    // Comment until end of line.
    do
      current_char = getchar();
    while (current_char != EOF && current_char != '\n' && current_char != '\r');

    if (current_char != EOF)
      return eat();
  }

  // Check for end of file.  Don't eat the EOF.
  if (current_char == EOF)
    return tok_eof;

  // Otherwise, just return the character as its ascii value.
  int previous_char = current_char;
  current_char = getchar();
  return previous_char;
}
