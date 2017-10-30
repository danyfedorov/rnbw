#ifndef RNBW_ARG_PARSER_H_INCLUDED
#define RNBW_ARG_PARSER_H_INCLUDED

#include "./grammar/rnbwLexer.h"
#include "./grammar/rnbwParser.h"

#include <vector>

struct antlr_context_t {
     pANTLR3_INPUT_STREAM input;
     prnbwLexer lxr;
     pANTLR3_COMMON_TOKEN_STREAM tstream;
     prnbwParser psr;
     rnbwParser_rnbw_return ast;
};

struct arg_parser_result_t {
     std::vector<unsigned> path;
     float angle;
     unsigned width;
};

arg_parser_result_t parse_arguments(int argc, char** argv);

#endif // RNBW_ARG_PARSER_H_INCLUDED
