#include <iostream>
#include <string>
#include "clrs.h"

#define SPC << " " <<
#define SGR(arg) << "\u001b[" << arg << "m" <<

using std::cin;
using std::cout;
using std::endl;
using std::string;

void read_input(string &input, int &lines, int &cols){
    lines = 0;
    cols = 0;
    input = "";

    string line;

    while (getline(cin, line)) {
        ++lines;
        int len = line.length();
        if (len > cols) {
            cols = len;
        }
        input += "\n" + line;
    }
}

int* mkpath(unsigned int c1, unsigned int c2){
    // TODO
    return 0;
}

int main(int argc, char** argv) {
    int lines;
    int cols;

    string input;
    input.reserve(10000);

    read_input(input, lines, cols);

    // cout SGR("38;5;57") input << endl;
    // cout << clrs[45].name SPC clrs[45].rgb SPC hex2rgb(clrs[45].rgb).r SPC hex2rgb(clrs[45].rgb).g SPC hex2rgb(clrs[45].rgb).b << endl;
    // cout << 40 SPC 255 SPC 10 SPC "-->" SPC rgb2hex(40, 255, 10) SPC "sould be 28ff0a" << endl;



    return 0;
}
