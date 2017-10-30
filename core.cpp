// this
#include "core.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <assert.h>

using std::vector;
using std::string;

string upcase_str(string &s) {
    for (auto & c: s) c = toupper(c);
    return s;
}

string downcase_str(string &s) {
    for (auto & c: s) c = tolower(c);
    return s;
}

char* upcase_cstr(char* s) {
    for (char* ch = s; *ch; ++ch) *ch = toupper(*ch);
    return s;
}

char* downcase_cstr(char* s) {
    for (char* ch = s; *ch; ++ch) *ch = tolower(*ch);
    return s;
}

path_order_t str_to_order(string s) {
    upcase_str(s);

    if (s == "RGB") {
        return RGB;
    } else if (s == "RBG") {
        return RBG;
    } else if (s == "GRB") {
        return GRB;
    } else if (s == "GBR") {
        return GBR;
    } else if (s == "BRG") {
        return BRG;
    } else if (s == "BGR") {
        return BGR;
    } else {
        std::ostringstream err_msg;
        err_msg << "rnbw: " << s << " does not designate RGB order";
        throw std::runtime_error(err_msg.str());
    }
}

path_sort_t str_to_sort(string s) {
    upcase_str(s);

    if (s == "LINE") {
        return LINE;
    } else if (s == "YARN") {
        return YARN;
    } else if (s == "EDGES") {
        return EDGES;
    } else {
        std::ostringstream err_msg;
        err_msg << "rnbw: " << s << " does not designate path sort (LINE, YARN, EDGES)";
        throw std::runtime_error(err_msg.str());
    }
}

path_order_t invert_order(path_order_t order) {
    if (order == RGB) {
        return BGR;
    } else if (order == RBG) {
        return GBR;
    } else if (order == GRB) {
        return BRG;
    } else if (order == GBR) {
        return RBG;
    } else if (order == BRG) {
        return GRB;
    } else if (order == BGR) {
        return RGB;
    } else {
        std::ostringstream err_msg;
        err_msg << "rnbw: " << order << " does not designate RGB order";
        throw std::runtime_error(err_msg.str());
    }
}

void extract_heximal_rgb(unsigned n, unsigned &r, unsigned &g, unsigned &b) {
    if (n > 215) {
        std::ostringstream err_msg;
        err_msg << "rnbw: " << n << " is over 215";
        throw std::runtime_error(err_msg.str());
    }
    b = n % 6;
    n = (n - b) / 6;
    g = n % 6;
    n = (n - g) / 6;
    r = n % 6;
}

void mkpath_edges_sort_aux(vector<unsigned> &path, unsigned &comp, int dcomp, unsigned cap, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path.push_back(comp * coef + common + 16);
    }
}

vector<unsigned> mkpath(unsigned from, unsigned to, path_order_t order, path_sort_t sort) {
    // TODO: make entry points
    assert((from >= 16) && (from <= 231));
    assert((to >= 16) && (to <= 231));

    from -= 16;
    to -= 16;

    unsigned r1, g1, b1, r2, g2, b2;
    extract_heximal_rgb(from, r1, g1, b1);
    extract_heximal_rgb(to, r2, g2, b2);

    int dr, dg, db;
    (r2 > r1) ? dr = 1 : dr = -1;
    (g2 > g1) ? dg = 1 : dg = -1;
    (b2 > b1) ? db = 1 : db = -1;

    vector<unsigned> path;
    path.push_back(r1 * 36 + g1 * 6 + b1 + 16);
    switch (sort) {
    case LINE:
        break;
    case YARN:
        break;
    case EDGES:
        switch (order) {
        case RGB:
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            break;
        case RBG:
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            break;
        case GRB:
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            break;
        case GBR:
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            break;
        case BRG:
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            break;
        case BGR:
            mkpath_edges_sort_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
            mkpath_edges_sort_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
            mkpath_edges_sort_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
            break;
        }
    }
    return path;
}
