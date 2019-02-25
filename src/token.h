#pragma once

#include <string>

namespace Token {


  // The lexer returns tokens [0-255] if it is an unknown character, otherwise one
  // of these for known things.
  enum Token
    {
     tok_eof,
     tok_unk,

     // commands
     tok_def,
     tok_extern,

     // arithmetic
     tok_plus,
     tok_minus,
     tok_mul,
     tok_div,

     // things
     tok_semi,
     tok_oparen,
     tok_cparen,
     tok_obrace,
     tok_cbrace,
     tok_obracket,
     tok_cbracket,

     // primary
     tok_identifier,
     tok_number,
    };

  enum TokenType
    {
     Id,
     Number,

     Def,
     Extern,

     Semi,
     OParen,
     CParen,
     OBrace,
     CBrace,
     OBracket,
     CBracket,
    };

}
