#ifndef RNBW_ARG_PARSER_H_INCLUDED
#define RNBW_ARG_PARSER_H_INCLUDED

#include <vector>

enum path_order_t { RGB, RBG, GRB, GBR, BRG, BGR };

struct arg_parser_result_t {
     path_order_t order;
     std::vector<unsigned> path;
     float angle;
     unsigned width;
};

arg_parser_result_t parse_arguments(int argc, char** argv);

#endif // RNBW_ARG_PARSER_H_INCLUDED
