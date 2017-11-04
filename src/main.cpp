// internal
#include "clrs.h"
#include "arg_parser.h"

// external
#include "utf8.h"

// std
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// settings
static const string escape = "\u001b[";
static const float eps = 0.0001;

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

    // decide on source of text
    std::istream *input_stream;
    std::ifstream f;
    if ((r.filename == "") || (r.filename == "-")) {
        input_stream = &cin;
    } else {
        f.open(r.filename.c_str());
        input_stream = &f;
    }

    string line;
    string::iterator it;
    unsigned color_i;
    float x;
    unsigned y_i = 0;
    unsigned x_i = 0;

    while (getline(*input_stream, line)) {
        x_i = 0;
        it = line.begin();
        while(it != line.end()) {
            /*   Find x coordinate of this point in the basis
             *   turned by r.angle degrees counterclockwise
             *   (when 90 degrees means no turning):
             *       x = sin(r.angle) * x_i - cos(r.angle) * y_i;
             *
             *   And that is fine if you are drawing with (0,0)
             *   in the lower left corner, but our (0,0) point
             *   is in the upper left.
             *
             *   If you enter 30 degrees, then with the graph
             *   flipped around Ox it would look like, 180 - 30 degrees
             *   to you on the output.
             *
             *   So to flip a graph back I do r.angle = (180 - r.angle)
             *
             *   Considering
             *      cos(180 - x) = -cos(x)
             *      sin(180 - x) = sin(x)
             *   there is the formula:
             *      x = cos(r.angle) * y_i + sin(r.angle) * x_i;
             */
            x = cos(r.angle) * y_i + sin(r.angle) * x_i;

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

    f.close();

    return 0;
}
