#include "arg_parser.h"

#include "clrs.h"

#include <string>
#include <stdexcept>
#include <assert.h>

#define _USE_MATH_DEFINES
#include <math.h>

using std::string;
using std::vector;

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

void mkpath_aux(vector<unsigned> &path, unsigned &comp, int dcomp, unsigned cap, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path.push_back(comp * coef + common + 16);
    }
}

vector<unsigned> mkpath(unsigned from, unsigned to, path_order_t order) {
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
    switch (order) {
    case RGB:
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        break;
    case RBG:
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        break;
    case GRB:
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        break;
    case GBR:
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        break;
    case BRG:
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        break;
    case BGR:
        mkpath_aux(path, b1, db, b2, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, g1, dg, g2, 6, r1 * 36 + b1);
        mkpath_aux(path, r1, dr, r2, 36, g1 * 6 + b1);
        break;
    }
    return path;
}

vector<string> args_to_vector(int argc, char** argv) {
    vector<string> res;
    for (int i = 1; i < argc; ++i) {
        res.push_back(string(argv[i]));
    }
    return res;
}

unsigned parse_color(string col) {
    if (std::isdigit(col[0])) {
        return std::stoi(col);
    } else {
        return colornum_from_colorname(col);
    }
}

bool is_option(string s) {
    return (s[0] == '-');
}

struct grad_t {
     unsigned from;
     unsigned to;
     bool back;
     bool including;
};

vector<grad_t> parse_colors(vector<string>::iterator &it, vector<string>::iterator end) {
    vector<grad_t> colors;
    unsigned c1, c2;
    do {
        if ((it != end) && !is_option(*it)) {
            c1 = parse_color(*it);
            ++it;
        } else {
            throw std::runtime_error("rnbw: expected color after -c");
        }

        if ((it != end) && !is_option(*it) && (*it == "to")) {
            ++it;
            if ((it != end) && !is_option(*it)) {
                c2 = parse_color(*it);
                ++it;
            } else {
                throw std::runtime_error("rnbw: expected color after 'to'");
            }

            if ((it != end) && !is_option(*it) && (*it == "back")) {
                ++it;
                colors.push_back({c1, c2, true, false});
                if ((it != end) && !is_option(*it) && (*it == "including")) {
                    ++it;
                    colors.push_back({c1, c2, true, true});
                }
            } else {
                colors.push_back({c1, c2, false, false});
            }
        } else {
            colors.push_back({c1, c1, false, false});
        }
    } while ((it != end) && !is_option(*it));

    return colors;
}

path_order_t str_to_order(string s) {
    for (auto & c: s) c = toupper(c);

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

path_order_t invert(path_order_t order) {
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

vector<unsigned> getpath(vector<grad_t> colors, path_order_t order) {
    vector<unsigned> path;
    vector<unsigned> tmp_path;
    for (auto it : colors) {
        if (it.from == it.to) {
            path.push_back(it.from);
        } else {
            tmp_path = mkpath(it.from, it.to, order);
            path.insert(path.end(), tmp_path.begin(), tmp_path.end());
            if (it.back) {
                tmp_path = mkpath(it.to, it.from, invert(order));
                path.insert(path.end(),
                            tmp_path.begin() + 1,
                            (it.including) ? tmp_path.end() : tmp_path.end() - 1);
            }
        }
    }
    return path;
}

arg_parser_result_t parse_arguments(int argc, char** argv) {
    arg_parser_result_t res;

    res.path = mkpath(33, 158, RGB);
    res.angle = M_PI / 6;
    res.width = 2;

    vector<string> args = args_to_vector(argc, argv);
    vector<string>::iterator it = args.begin();
    vector<string>::iterator end = args.end();

    path_order_t order;

    vector<grad_t> colors;

    while (it != end) {
        if ((*it == "-c") || (*it == "--colors")) {
            ++it;
            colors = parse_colors(it, end);
        } else if ((*it == "-o") || (*it == "--order")) {
            ++it;
            order = str_to_order(*it);
            ++it;
        } else if ((*it == "-a") || (*it == "--angle")) {
            ++it;
            res.angle = stoi(*it) * M_PI / 180;
            ++it;
        } else if ((*it == "-w") || (*it == "--width")) {
            ++it;
            res.width = stoi(*it);
            ++it;
        }
    }

    if (!colors.empty()) {
        res.path = getpath(colors, order);
    }
    return res;
}
