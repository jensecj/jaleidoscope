#pragma once

#include <string>
#include <string_view>
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





char look(int point, std::string_view s) {
  if(point >= s.length()) {
    return EOF;
  } else {
    return s[point];
  }
}

int eat_whitespace(int point, std::string_view s) {
  while (isspace(look(point, s))) {
    point++;
  }

  return point;
}

int eat_line(int point, std::string_view s) {
  char c = look(point, s);

  while (c != EOF && c != '\n' && c != '\r') {
    c = look(++point, s);
  }

  return point;
}

std::vector<Token::Token> _lex(int point, std::string_view input) {
  std::vector<Token::Token> output;

  int current_char = look(point, input);

  while (current_char != EOF) {
    point = eat_whitespace(point, input);
    current_char = look(point, input);

    // identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(current_char)) {
      IdentifierStr = current_char;

      while (isalnum((current_char = look(++point, input)))) {
        IdentifierStr += current_char;
      }

      if (token_map.find(IdentifierStr) != token_map.end()) {
        output.push_back(token_map[IdentifierStr]);
        continue;
      }

      output.push_back(Token::tok_identifier);
      continue;
    }

    // Number: [0-9.]+
    if (isdigit(current_char) || current_char == '.') {
      std::string num;

      do {
        num += current_char;
        current_char = look(++point, input);
      } while (isdigit(current_char) || current_char == '.');

      NumVal = strtod(num.c_str(), nullptr);
      output.push_back(Token::tok_number);
      continue;
    }

    if (current_char == '#') {
      point = eat_line(point, input);
      current_char = look(point, input);
    }

    switch (current_char) {
    case '+': output.push_back(Token::tok_plus); break;
    case '-': output.push_back(Token::tok_minus); break;
    case '*': output.push_back(Token::tok_mul); break;
    case '/': output.push_back(Token::tok_div); break;
    case ';': output.push_back(Token::tok_semi); break;
    case '(': output.push_back(Token::tok_oparen); break;
    case ')': output.push_back(Token::tok_cparen); break;
    case '[': output.push_back(Token::tok_obracket); break;
    case ']': output.push_back(Token::tok_cbracket); break;
    case '{': output.push_back(Token::tok_obrace); break;
    case '}': output.push_back(Token::tok_cbrace); break;
    case EOF: output.push_back(Token::tok_eof); break;
    }

    // Otherwise, just return the character as its ascii value.
    // int previous_char = current_char;
    current_char = look(++point, input);
  }

  return output;
}

std::vector<Token::Token> lex(std::string_view input) {
  return _lex(0, input);
}
