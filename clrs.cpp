#include "clrs.h"

using std::string;
using std::stringstream;

rgb_t hex2rgb(string s) {
    stringstream ss;
    unsigned int r, g, b;

    ss << std::hex << s[0] << s[1];
    ss >> r;

    ss.clear();
    ss.str(string());

    ss << std::hex << s[2] << s[3];
    ss >> g;

    ss.clear();
    ss.str(string());

    ss << std::hex << s[4] << s[5];
    ss >> b;

    return {r, g, b};
}

string rgb2hex(rgb_t rgb) {
    stringstream ss;
    string r, g, b;

    ss << std::hex << rgb.r;
    ss >> r;
    if (r.length() == 1) { r = "0" + r; };

    ss.clear();
    ss.str(string());

    ss << std::hex << rgb.g;
    ss >> g;
    if (g.length() == 1) { g = "0" + g; };

    ss.clear();
    ss.str(string());

    ss << std::hex << rgb.b;
    ss >> b;
    if (b.length() == 1) { b = "0" + b; };

    return r + g + b;
}

string rgb2hex(unsigned r, unsigned g, unsigned b) {
    return rgb2hex({r, g, b});
}

int colornum_from_colorname(string name) {
    for (int i = 0; i < 256; i++) {
        if ((colors[i].name == name) || (colors[i].simpler_name == name)) {
            return i;
        }
    }
    return -1;
}

string colorname_from_colornum(unsigned num) {
    if (colors[num].simpler_name != "") {
        return colors[num].simpler_name;
    } else {
        return colors[num].name;
    }
}
