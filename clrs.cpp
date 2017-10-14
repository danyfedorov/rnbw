#include "clrs.h"

Rgb hex2rgb(std::string s) {
    std::stringstream ss;
    unsigned int r, g, b;

    ss << std::hex << s[0] << s[1];
    ss >> r;

    ss.clear();
    ss.str(std::string());

    ss << std::hex << s[2] << s[3];
    ss >> g;

    ss.clear();
    ss.str(std::string());

    ss << std::hex << s[4] << s[5];
    ss >> b;

    return {r, g, b};
}

std::string rgb2hex(Rgb rgb) {
    std::stringstream ss;
    std::string r, g, b;

    ss << std::hex << rgb.r;
    ss >> r;
    if (r.length() == 1) { r = "0" + r; };

    ss.clear();
    ss.str(std::string());

    ss << std::hex << rgb.g;
    ss >> g;
    if (g.length() == 1) { g = "0" + g; };

    ss.clear();
    ss.str(std::string());

    ss << std::hex << rgb.b;
    ss >> b;
    if (b.length() == 1) { b = "0" + b; };

    return r + g + b;
}

std::string rgb2hex(unsigned int r, unsigned int g, unsigned int b) {
    return rgb2hex({r, g, b});
}
