// internal
#include "clrs.h"
#include "arg_parser.h"

// external
#include "utf8.h"

// std
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

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

void one_utf8_char_out(string::iterator &it, string::iterator line_end) {
    string::iterator it_utf8_char_end = it;
    utf8::advance(it_utf8_char_end, 1, line_end);
    while (it != it_utf8_char_end) {
        cout << *it;
        ++it;
    }
}

int main(int argc, char** argv) {
    arg_parser_result_t r;

    r = parse_arguments(argc, argv);
    cout << "o " << r.order << endl;
    cout << "a " << r.angle << endl;
    cout << "w " << r.width << endl;
    for (auto i : r.path) {
        cout << i << " ";
    }
    cout << endl;

    string line;
    string::iterator it;
    unsigned color_i;
    float x;
    unsigned y_i = 0;
    unsigned x_i = 0;
    while (getline(cin, line)) {
        x_i = 0;
        it = line.begin();
        while(it != line.end()) {
            x = cos(r.angle) * y_i + sin(r.angle) * x_i; // turn argument

            if (fabs(ceil(x) - x) < eps) x = ceil(x); // fix errors
            if (fabs(floor(x) - x) < eps) x = floor(x);

            if (x < 0) {
                color_i = abs(ceil(x / r.width));
                color_i %= r.path.size();
                color_i = r.path.size() - 1 - color_i;
            } else {
                color_i = abs(floor(x / r.width));
                color_i %= r.path.size();
            }
            setf(r.path[color_i]);

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
