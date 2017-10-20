// internal
#include "clrs.h"

// external
#include "utf8.h"

// std
#include <iostream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>

// TODO remove
#define SPC << " " <<

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// settings
const string escape = "\u001b[";
const float eps = 0.0001;

inline void setf(unsigned c) {
    if (c < 16) {
        cout << escape << c + 30 << "m";
    } else {
        cout << escape << "38;5;" << c << "m";
    }
}

inline void setb(size_t c) {
    if (c < 16) {
        cout << escape << c + 40 << "m";
    } else {
        cout << escape << "48;5;" << c << "m";
    }
}

inline void reset() {
    cout << escape << "0m";
}

enum PathOrder { RGB, RBG, GRB, GBR, BRG, BGR };

void extract_heximal_rgb(size_t n, size_t &r, size_t &g, size_t &b) {
    if (n > 215) {
        std::ostringstream err_msg;
        err_msg << n << " is over 215";
        throw std::runtime_error(err_msg.str());
    }
    b = n % 6;
    n = (n - b) / 6;
    g = n % 6;
    n = (n - g) / 6;
    r = n % 6;
}

void mkpath_aux(vector<int> &path, size_t &comp, int dcomp, size_t cap, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path.push_back(comp * coef + common + 16);
    }
}

vector<int> mkpath(size_t from, size_t to, PathOrder order) {
    assert((from >= 16) && (from <= 231));
    assert((to >= 16) && (to <= 231));

    from -= 16;
    to -= 16;

    size_t r1, g1, b1, r2, g2, b2;
    extract_heximal_rgb(from, r1, g1, b1);
    extract_heximal_rgb(to, r2, g2, b2);

    int dr, dg, db;
    (r2 > r1) ? dr = 1 : dr = -1;
    (g2 > g1) ? dg = 1 : dg = -1;
    (b2 > b1) ? db = 1 : db = -1;

    vector<int> path;
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

void one_utf8_char_out(string::iterator &it, string::iterator line_end) {
    string::iterator it_utf8_char_end = it;
    utf8::advance(it_utf8_char_end, 1, line_end);
    while (it != it_utf8_char_end) {
        cout << *it;
        ++it;
    }
}

int main(int argc, char** argv) {
    // args
    size_t from = std::strtol(argv[1], 0, 10);
    size_t to = std::strtol(argv[2], 0, 10);
    size_t ordr = std::strtol(argv[3], 0, 10);
    float ang = std::strtol(argv[4], 0, 10) * M_PI / 180; // convert to radians
    int width = std::strtol(argv[5], 0, 10);

    vector<int> pth(16);
    pth = mkpath(from, to, static_cast<PathOrder>(ordr));

    string line;
    string::iterator it;
    size_t color_i;
    float x;
    size_t y_i = 0;
    size_t x_i = 0;
    while (getline(cin, line)) {
        x_i = 0;
        // utf8_ch_num = utf8::distance(line.begin(), line.end());
        it = line.begin();
        while(it != line.end()) {
            x = cos(ang) * y_i + sin(ang) * x_i; // turn argument

            if (fabs(ceil(x) - x) < eps) x = ceil(x); // fix errors
            if (fabs(floor(x) - x) < eps) x = floor(x);

            if (x < 0) {
                color_i = abs(ceil(x / width));
                color_i %= pth.size();
                color_i = pth.size() - 1 - color_i;
            } else {
                color_i = abs(floor(x / width));
                color_i %= pth.size();
            }
            setf(pth[color_i]);

            // one square unit is two chars
            // first char
            one_utf8_char_out(it, line.end());
            // second char
            if (it != line.end()) {
                one_utf8_char_out(it, line.end());
            }

            ++x_i;
        }

        cout << endl;
        ++y_i;
    }

    return 0;
}
