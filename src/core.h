#ifndef RNBW_CORE_H_INCLUDED
#define RNBW_CORE_H_INCLUDED

#include <vector>
#include <string>

// data

enum path_order_t { RGB, RBG, GRB, GBR, BRG, BGR };

enum path_sort_t { LINE, YARN, EDGES };

// functions

path_order_t invert_order(path_order_t order);

path_order_t str_to_order(std::string s);

path_sort_t str_to_sort(std::string s);

std::vector<unsigned> mkpath(unsigned from, unsigned to, path_order_t order, path_sort_t sort);

char* downcase_cstr(char* s);

#endif // RNBW_CORE_H_INCLUDED
