#include <iostream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <array>
#include <cstdlib>

#define _USE_MATH_DEFINES
#include <math.h>

#include "clrs.h"

// TODO remove
#define SPC << " " <<

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::array;

const string escape = "\u001b[";

inline void setf(unsigned c) {
    if (c < 16) {
        cout << escape << c + 30 << "m";
    } else {
        cout << escape << "38;5;" << c << "m";
    }
}

inline void setb(unsigned c) {
    if (c < 16) {
        cout << escape << c + 40 << "m";
    } else {
        cout << escape << "48;5;" << c << "m";
    }
}

inline void reset() {
    cout << escape << "0m";
}

enum Pth { RGB, RBG, GRB, GBR, BRG, BGR };

void extract_heximal_rgb(unsigned n, unsigned &r, unsigned &g, unsigned &b) {
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

void mkpath_aux(vector<int> &path, unsigned &comp, int dcomp, unsigned cap, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path.push_back(comp * coef + common + 16);
    }
}

vector<int> mkpath(unsigned from, unsigned to, Pth order) {
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

int main(int argc, char** argv) {
    // args
    unsigned from = std::strtol(argv[1], 0, 10);
    unsigned to = std::strtol(argv[2], 0, 10);
    unsigned ordr = std::strtol(argv[3], 0, 10);
    float ang = std::strtol(argv[4], 0, 10) * M_PI / 180; // convert to radians
    int width = std::strtol(argv[5], 0, 10);

    vector<int> pth(16);
    pth = mkpath(from, to, static_cast<Pth>(ordr));

    string line;
    unsigned pthi;
    float x;
    unsigned y_i = 0;
    unsigned x_i = 0;
    while (getline(cin, line)) {
        pthi = 0;
        x_i = 0;
        while(2*x_i < line.length()) {
            x = cos(ang) * y_i + sin(ang) * x_i; // turn argument

            if (abs(ceil(x) - x) < 0.001) x = ceil(x); // fix errors
            if (abs(floor(x) - x) < 0.001) x = floor(x);

            pthi = abs(floor(x / width)) % pth.size(); // use function with turned arg

            if (x < 0) {
                setf((pthi == 0) ? pth[0] : pth[pth.size() - pthi]);
            } else {
                setf(pth[pthi]);
            }

            // one square unit is two chars
            cout << line[2*x_i];
            if (2*x_i + 1 < line.length()) {
                cout << line[2*x_i + 1];
            }
            ++x_i;
        }

        cout << endl;
        ++y_i;
    }

    return 0;
}
