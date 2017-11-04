#ifndef RNBW_ARG_PARSER_H_INCLUDED
#define RNBW_ARG_PARSER_H_INCLUDED

#include "../grammar/rnbwLexer.h"
#include "../grammar/rnbwParser.h"

#include <vector>
#include <string>

struct arg_parser_result_t {
     std::vector<unsigned> path;
     float angle;
     unsigned width;
     std::string filename;
     bool background;
};

arg_parser_result_t parse_arguments(int argc, char** argv);

#endif // RNBW_ARG_PARSER_H_INCLUDED
