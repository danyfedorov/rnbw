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

#define SPC << " " <<
#define PL(S) std::cout << S << std::endl
#define NL std::cout << std::endl
// using std::cout;
// using std::endl;

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
//     std::cout << s << ": " << a.r SPC a.g SPC a.b << std::endl;
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

// entry points stuff

unsigned grey_to_rgb(unsigned num) {
    assert(num > 231);
    switch (num) {
    case 238: return 59;
    case 244: return 102;
    case 249: return 145;
    case 252: return 188;
    case 255: return 231;
    }
    // to calm the -Wall
    return num;
}

unsigned rgb_to_grey(unsigned num) {
    // PL("rgb2grey" SPC num);
    switch (num) {
    case 59: return 238;
    case 102: return 244;
    case 145: return 249;
    case 188: return 252;
    case 231: return 255;
    }
    throw std::runtime_error("wut1");
}

unsigned find_grey_corresponding_entry(unsigned num) {
    assert(num > 231);
    if (num <= 238) {
        return 238;
    } else if (num <= 244) {
        return 244;
    } else if (num <= 249) {
        return 249;
    } else if (num <= 252) {
        return 252;
    } else if (num <= 255) {
        return 255;
    }
    // to calm the -Wall
    return num;
}

unsigned come_to_grey_entry_point(vector<unsigned>& path, unsigned num) {
    assert(num > 231);
    unsigned to = find_grey_corresponding_entry(num);

    for (unsigned i = num; i < to; ++i) {
        path.push_back(i);
    }

    unsigned res = grey_to_rgb(to);
    path.push_back(res);

    return res;
}

unsigned find_rgb_corresponding_entry_point(unsigned num) {
    assert(num < 16);
    switch (num) {
    case 0:  return 16;
    case 1:  return 160;
    case 2:  return 34;
    case 3:  return 136;
    case 4:  return 24;
    case 5:  return 60;
    case 6:  return 38;
    case 7:  return 188;
    case 8:  return 145;
    case 9:  return 196;
    case 10: return 82;
    case 11: return 227;
    case 12: return 67;
    case 13: return 139;
    case 14: return 51;
    case 15: return 231;
    }
    // to calm the -Wall
    return num;
}

unsigned come_to_entry_point(vector<unsigned>& path, unsigned num) {
    unsigned newn;
    if (num < 16) {
        newn = find_rgb_corresponding_entry_point(num);
        path.push_back(newn);
    } else if (num > 231) {
        newn = come_to_grey_entry_point(path, num);
    } else {
        newn = num;
        path.push_back(num);
    }
    return newn;
}

unsigned find_corresponding_entry_point(unsigned num) {
    if (num < 16) {
        return find_rgb_corresponding_entry_point(num);
    } else if (num > 231) {
        return grey_to_rgb(find_grey_corresponding_entry(num));
    } else {
        return num;
    }
}

inline bool isgrey(unsigned num) {
    return ((num > 231) && (num < 256));
}

vector<unsigned> mk_grey_path(unsigned from, unsigned to) {
    int d;
    vector<unsigned> path;
    (from < to) ? d = 1 : d = -1 ;
    for (unsigned i = from; i != to; i += d) {
        path.push_back(i);
    }
    path.push_back(to);

    // for (auto i : path) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    return path;
}

void add_potential_grey_path(vector<unsigned>& path, unsigned from, unsigned to) {
    if (isgrey(to)) {
        unsigned grey_from = rgb_to_grey(from);
        vector<unsigned> add = mk_grey_path(grey_from, to);
        path.insert(path.end(), add.begin() + 1, add.end());
    }
}

// toplevel mkpath

vector<unsigned> mkpath(unsigned from_10base, unsigned to_10base, path_order_t order, path_sort_t sort) {
    assert(from_10base < 256);
    assert(to_10base < 256);

    if (isgrey(from_10base) && isgrey(to_10base)) {
        return mk_grey_path(from_10base, to_10base);
    }

    vector<unsigned> path;

    // PL("before" SPC from_10base SPC to_10base);

    from_10base = come_to_entry_point(path, from_10base);
    unsigned new_to_10base;
    new_to_10base = find_corresponding_entry_point(to_10base);

    // PL("after" SPC from_10base SPC new_to_10base);

    from_10base -= 16;
    new_to_10base -= 16;

    rgb_t from = num2rgb(from_10base);
    rgb_t to = num2rgb(new_to_10base);

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

    add_potential_grey_path(path, new_to_10base + 16, to_10base);

    for (auto i : path) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return path;
}
