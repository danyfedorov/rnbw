#include <iostream>
#include <string>
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <cstdlib>

#include "clrs.h"

// TODO remove
#define SPC << " " <<
#define SGR(arg) "\u001b[" << arg << "m"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

const string escape = "\u001b[";

void read_input(vector<string> &input, int &cols){
    cols = 0;

    string line;

    while (cin >> line) {
        int len = line.length();
        if (len > cols) {
            cols = len;
        }

        input.push_back(line);
    }
}

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

string pth2str(Pth ordr) {
    switch (ordr) {
    case RGB:
        return "RGB";
        break;
    case RBG:
        return "RBG";
        break;
    case GRB:
        return "GRB";
        break;
    case GBR:
        return "GBR";
        break;
    case BRG:
        return "BRG";
        break;
    case BGR:
        return "BGR";
        break;
    }
    return "---";
}

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

void mkpath_aux(int* path, unsigned &comp, int dcomp, unsigned cap, int &i, int coef, int common) {
    while (comp != cap) {
        comp += dcomp;
        path[i] = comp * coef + common + 16;
        // cout << coef SPC comp SPC cap SPC path[i] << endl;
        ++i;
    }
}

int* mkpath(int &size, unsigned from, unsigned to, Pth order) {
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

    int* path = new int[16];
    path[0] = r1 * 36 + g1 * 6 + b1 + 16;
    int i = 1;
    switch (order) {
    case RGB:
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        break;
    case RBG:
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        break;
    case GRB:
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        break;
    case GBR:
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        break;
    case BRG:
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        break;
    case BGR:
        mkpath_aux(path, b1, db, b2, i, 1, r1 * 36 + g1 * 6);
        mkpath_aux(path, g1, dg, g2, i, 6, r1 * 36 + b1);
        mkpath_aux(path, r1, dr, r2, i, 36, g1 * 6 + b1);
        break;
    }
    size = i;
    return path;
}

void test() {
    // setf(203);
    // cout << "opana" << endl;
    // setb(155);
    // cout << "faffed";
    // reset();

    // cout << endl << fromname("grey-53") SPC "sould be 102" << endl;
    // cout << clrs[45].name SPC clrs[45].rgb SPC hex2rgb(clrs[45].rgb).r SPC hex2rgb(clrs[45].rgb).g SPC hex2rgb(clrs[45].rgb).b << endl;
    // cout << 40 SPC 255 SPC 10 SPC "-->" SPC rgb2hex(40, 255, 10) SPC "sould be 28ff0a" << endl;

    // unsigned r, g, b;
    // extract_heximal_rgb(131, r, g, b);
    // cout << r SPC g SPC b << endl;

    // int* pth;
    // int size;
    // cout << endl;
    // pth = mkpath(size, 16, 231, RGB);
    // for (int i = 0; i < size; ++i) {
    //     cout << pth[i] << endl;
    // }

    // cout << "-----" << endl;

    // pth = mkpath(size, 231, 16, BGR);
    // for (int i = 0; i < size; ++i) {
    //     cout << pth[i] << endl;
    // }
}

void demo(){
    int size;
    int* pth = mkpath(size, 231, 16, BGR);
    setb(233);
    cout << "231->16" << endl << "BGR ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    reset();
    setb(233);
    //
    pth = mkpath(size, 16, 231, RGB);
    cout << "16->231" << endl << "RGB ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    pth = mkpath(size, 16, 231, RBG);
    cout << "RBG ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    pth = mkpath(size, 16, 231, BRG);
    cout << "BRG ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    pth = mkpath(size, 16, 231, BGR);
    cout << "BGR ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    pth = mkpath(size, 16, 231, GRB);
    cout << "GRB ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    pth = mkpath(size, 16, 231, GBR);
    cout << "GBR ";
    for (int i = 0; i < size; ++i) {
        setf(pth[i]);
        cout << "@@@@@@@";
    }
    cout << endl;
    reset();
}

int main(int argc, char** argv) {
    int cols;

    unsigned from = std::strtol(argv[1], 0, 10);
    unsigned to = std::strtol(argv[2], 0, 10);
    unsigned ordr = std::strtol(argv[3], 0, 10);
    cout << pth2str(static_cast<Pth>(ordr)) << endl;

    vector<string> input;

    read_input(input, cols);

    int size;
    int* pth = mkpath(size, from, to, static_cast<Pth>(ordr));
    int pthi = 0;
    bool back = false;
    for (auto i = input.begin(); i != input.end(); ++i) {
        pthi = 0;
        back = false;
        for (unsigned j = 0; j < i->length(); ++j) {
            if (pthi == size) {
                back = true;
                pthi -= 2;
            } else if (pthi == -1) {
                back = false;
                pthi += 2;
            }
            setf(pth[pthi]);
            cout << (*i)[j];
            back ? --pthi : ++pthi;
        }
        cout << endl;
    }

    // demo();
    

    test();

    return 0;
}
