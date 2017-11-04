// this
#include "core.h"

#include <string>
#include <sstream>
#include <stdexcept>
#include <assert.h>
#include <iostream>

#include <math.h>

using std::vector;
using std::string;

#define WS << " " <<
#define WS_ << " "
using std::cout;
using std::endl;

// utils

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

// sort and order enums operations

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

// rgb_t

struct rgb_t {
     unsigned r, g, b;
};

// void prgb(string s, rgb_t a) {
//     cout << s << ": " << a.r WS a.g WS a.b << endl;
// }

unsigned rgb2num(rgb_t rgb) {
    return rgb.r * 36 + rgb.g * 6 + rgb.b;
}

rgb_t num2rgb(unsigned n) {
    if (n > 215) {
        std::ostringstream err_msg;
        err_msg << "rnbw: " << n << " is over 215";
        throw std::runtime_error(err_msg.str());
    }
    unsigned r, g, b;
    b = n % 6;
    n = (n - b) / 6;
    g = n % 6;
    n = (n - g) / 6;
    r = n % 6;
    return {r, g, b};
}

void unpack_rgb(rgb_t rgb, unsigned &r, unsigned &g, unsigned &b) {
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
}

void deltas(rgb_t from, rgb_t to, int &dr, int &dg, int &db) {
    (to.r > from.r) ? dr = 1 : dr = -1;
    (to.g > from.g) ? dg = 1 : dg = -1;
    (to.b > from.b) ? db = 1 : db = -1;
}

// mkpath edges sort

void mkpath_edges_sort_aux(vector<unsigned> &path, unsigned &comp, int dcomp, unsigned cap, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path.push_back(comp * coef + common + 16);
    }
}

void mkpath_edges_sort(vector<unsigned> &path, rgb_t from, rgb_t to, path_order_t order) {
    unsigned r1, g1, b1, r2, g2, b2;
    unpack_rgb(from, r1, g1, b1);
    unpack_rgb(to, r2, g2, b2);

    int dr, dg, db;
    deltas(from, to, dr, dg, db);

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

// mkpath line sort

inline int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

/* Point to line distance from p0 point to p1 -> p2 line
 *
 * The formula is:
 *   d01 = | [(r0 - r1) * s] | / |s|,
 * Where
 *   [a*b] - cross product
 *   |a|   - length of the a vector
 *   r0 - radius vector of a p0 point
 *   r1 - radius vector of a point on a line (p1 or p2 for instance)
 *   s  - vector parallel to the p1 -> p2 line
 *
 * Reference:
 *   http://cyclowiki.org/wiki/Расстояние_от_точки_до_прямой_в_трёхмерном_пространстве
 *
 * I use the second formula where cross product and length are expanded
 */
float distance_pl(rgb_t p1, rgb_t p2, rgb_t p0) {
    unsigned r0, g0, b0;
    unsigned r1, g1, b1;
    unsigned r2, g2, b2;

    unpack_rgb(p0, r0, g0, b0);
    unpack_rgb(p1, r1, g1, b1);
    unpack_rgb(p2, r2, g2, b2);

    int l = r2 - r1;
    int m = g2 - g1;
    int n = b2 - b1;

    int i = determinant(r0 - r1, g0 - g1, l, m);
    int j = determinant(g0 - g1, b0 - b1, m, n);
    int k = determinant(b0 - b1, r0 - r1, n, l);

    return sqrt(i*i + j*j + k*k) / sqrt(l*l + m*m + n*n);
}

rgb_t find_min_d_point(rgb_t cur, rgb_t from, rgb_t to, int dr, int dg, int db) {
    unsigned r1, g1, b1;
    unsigned r2, g2, b2;
    unsigned rc, gc, bc;

    unpack_rgb(from, r1, g1, b1);
    unpack_rgb(to, r2, g2, b2);
    unpack_rgb(cur, rc, gc, bc);

    float d; // distance
    float min_d;
    rgb_t point;
    rgb_t min_d_point;
    bool first = true;

    rc = cur.r;
    for (unsigned i = 0; i < 2; ++i) {
        gc = cur.g;
        for (unsigned j = 0; j < 2; ++j) {
            bc = cur.b;
            for (unsigned k = 0; k < 2; ++k) {
                if (! ((i == 0) && (j == 0) && (k == 0))) {
                    point = {rc, gc, bc};
                    d = distance_pl(from, to, point);

                    if (first) {
                        min_d = d;
                        min_d_point = point;
                        first = false;
                    } else if (d < min_d) {
                        min_d = d;
                        min_d_point = point;
                    }

                }
                bc += db;
            }
            gc += dg;
        }
        rc += dr;
    }

    return min_d_point;
}

void mkpath_line_sort(vector<unsigned> &path, rgb_t from, rgb_t to) {
    int dr, dg, db;
    deltas(from, to, dr, dg, db);

    rgb_t cur = from;
    while (!((cur.r == to.r) && (cur.g == to.g) && (cur.b == to.b))) {
        cur = find_min_d_point(cur, from, to, dr, dg, db);
        path.push_back(rgb2num(cur) + 16);
    }
}

// mkpath yarn sort

void mkpath_yarn_sort(vector<unsigned> &path, rgb_t from, rgb_t to, path_order_t order) {
    int dr, dg, db;
    deltas(from, to, dr, dg, db);

    rgb_t cur = from;
    rgb_t prev;
    while (!((cur.r == to.r) && (cur.g == to.g) && (cur.b == to.b))) {
        prev = cur;
        cur = find_min_d_point(cur, from, to, dr, dg, db);
        
        mkpath_edges_sort(path, prev, cur, order);
    }
}

// toplevel mkpath

vector<unsigned> mkpath(unsigned from_10base, unsigned to_10base, path_order_t order, path_sort_t sort) {
    // TODO: make entry points
    assert((from_10base >= 16) && (from_10base <= 231));
    assert((to_10base >= 16) && (to_10base <= 231));

    from_10base -= 16;
    to_10base -= 16;

    rgb_t from = num2rgb(from_10base);
    rgb_t to = num2rgb(to_10base);

    vector<unsigned> path;
    path.push_back((from.r * 36) + (from.g * 6) + from.b + 16);

    switch (sort) {
    case LINE:
        mkpath_line_sort(path, from, to);
        break;
    case YARN:
        mkpath_yarn_sort(path, from, to, order);
        break;
    case EDGES:
        mkpath_edges_sort(path, from, to, order);
    }

    for (auto i : path) {
        std::cout << i << " ";
    }
    cout << endl;

    return path;
}
