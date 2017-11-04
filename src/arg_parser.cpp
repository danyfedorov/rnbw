#include "arg_parser.h"

// internal
#include "core.h"
#include "clrs.h"

// std
#include <string>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

#define SPC << " " <<
#define PL(S) std::cout << S << std::endl
#define NL std::cout << std::endl

using std::string;
using std::vector;

struct antlr_context_t {
     pANTLR3_INPUT_STREAM input;
     prnbwLexer lxr;
     pANTLR3_COMMON_TOKEN_STREAM tstream;
     prnbwParser psr;
     rnbwParser_rnbw_return ast;
};

antlr_context_t get_antlr_context(char* input_arg) {
    pANTLR3_INPUT_STREAM input = antlr3NewAsciiStringCopyStream((pANTLR3_UINT8)input_arg, (ANTLR3_UINT32)strlen(input_arg), NULL);

    prnbwLexer lxr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    prnbwParser psr;
    rnbwParser_rnbw_return rnbwAST;

    lxr = rnbwLexerNew(input);

    if (lxr == NULL) {
        // fprintf(stderr, "rnbw: Unable to create the lexer due to malloc() failure1\n");
        throw std::runtime_error("rnbw: Unable to create the lexer due to malloc() failure1\n");
        // exit(ANTLR3_ERR_NOMEM);
    }

    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

    if (tstream == NULL) {
        // fprintf(stderr, "rnbw: Out of memory trying to allocate token stream\n");
        throw std::runtime_error("rnbw: Out of memory trying to allocate token stream\n");
        // exit(ANTLR3_ERR_NOMEM);
    }

    psr = rnbwParserNew(tstream);

    if (tstream == NULL) {
        // fprintf(stderr, "rnbw: Out of memory trying to allocate parser\n");
        throw std::runtime_error("rnbw: Out of memory trying to allocate parser\n");
        // exit(ANTLR3_ERR_NOMEM);
    }

    rnbwAST = psr->rnbw(psr);

    if (psr->pParser->rec->state->errorCount > 0) {
        fprintf(stderr, "rnbw: The parser returned %d errors, tree walking aborted.\n", psr->pParser->rec->state->errorCount);
        throw std::runtime_error("parser err");
    }
    // else {
    //     printf("1 Tree : %s\n", rnbwAST.tree->toStringTree(rnbwAST.tree)->chars);
    // }

    return (antlr_context_t){input, lxr, tstream, psr, rnbwAST};
}

void free_antlr_context(antlr_context_t a) {
    a.psr     ->free  (a.psr);      a.psr = NULL;
    a.tstream ->free  (a.tstream);	a.tstream = NULL;
    a.lxr	    ->free  (a.lxr);	    a.lxr = NULL;
    a.input   ->close (a.input);	  a.input = NULL;
}

unsigned get_argv_size(int argc, char** argv) {
    unsigned size = 0;
    for (int i = 1; i < argc; ++i) {
        size += strlen(argv[i]) + 1;
    }
    return size;
}

string pick_filename(int &argc, char** argv) {
    string filename;
    string str_arg;
    unsigned shift = 0;
    int i = 0;
    while (i < argc) {
        str_arg = string(argv[i]);
        if ((str_arg == "--file") || (str_arg == "-f")) {
            ++i;
            filename = string(argv[i]);
            shift += 2;
        } else if (shift) {
            argv[i - shift] = argv[i];
        }
        ++i;
    }

    argc -= shift;

    return filename;
}

char* concat(int argc, char** argv) {
    unsigned size = get_argv_size(argc, argv);

    char* retval = new char[size + 1]; // +1 for \0
    strcpy(retval, argv[1]);
    strcat(retval, " ");
    for (int i = 2; i < argc; ++i) {
        strcat(retval, argv[i]);
        strcat(retval, " ");
    }
    return retval;
}

class Node {
    public:
     explicit Node(pANTLR3_BASE_TREE ptr_arg) {
         ptr = ptr_arg;
         str = string((char*) ptr->toString(ptr)->chars);
         child_n = ptr->getChildCount(ptr);;
     }

     Node getChild(unsigned i) {
         return Node((pANTLR3_BASE_TREE) this->ptr->getChild(this->ptr, i));
     }

     pANTLR3_BASE_TREE ptr;
     string str;
     unsigned child_n;
};

unsigned get_colornum(Node color) {
    if (color.str == "COLORNUM") {
        return std::stoi(color.getChild(0).str);
    } else if (color.str == "COLORNAME") {
        return colornum_from_colorname(color.getChild(0).str);
    } else {
        throw std::runtime_error("bad color type to pass to get_colornum");
    }
}

vector<unsigned> parse_range(Node stripe, path_sort_t sort, path_order_t order) {
    string from_including = stripe.getChild(0).str;
    Node   from_color(stripe.getChild(1));

    string to_including = stripe.getChild(2).str;
    Node   to_color(stripe.getChild(3));

    Node back_node = stripe.getChild(4);
    string back = back_node.str;

    unsigned from_num = get_colornum(from_color);
    unsigned to_num = get_colornum(to_color);

    // std::cout << "      " << from_including << " " << from_color.str << " " << from_color.getChild(0).str << std::endl;
    // std::cout << "      " << to_including << " " << to_color.str << " " << to_color.getChild(0).str << std::endl;
    // std::cout << "      " << back_node.ptr->toStringTree(back_node.ptr)->chars << std::endl;

    vector<unsigned> retval = mkpath(from_num, to_num, order, sort);

    if (from_including == "NOT_INCLUDING") {
        retval.erase(retval.begin());
    } else if (!((from_including == "DEFAULT_INCLUDING") || (from_including == "INCLUDING"))) {
        throw std::runtime_error("not a valid including token");
    }

    if (to_including == "NOT_INCLUDING") {
        retval.pop_back();
    } else if (!((to_including == "DEFAULT_INCLUDING") || (to_including == "INCLUDING"))) {
        throw std::runtime_error("not a valid including token");
    }

    if (back != "NO_BACK") {
        string back_including = back_node.getChild(0).str;
        vector<unsigned> reversed = retval;
        std::reverse(reversed.begin(), reversed.end());
        if ((back_including == "DEFAULT_INCLUDING") || (back_including == "NOT_INCLUDING")) {
            retval.insert(retval.end(), reversed.begin() + 1, reversed.end() - 1);
        } else if (back_including == "INCLUDING") {
            retval.insert(retval.end(), reversed.begin() + 1, reversed.end());
        } else {
            throw std::runtime_error("not a valid including token");
        }
    }

    return retval;
}

vector<unsigned> mk_rainbow() {
    vector<unsigned> retval =
        {196,
         202, 208, 214, 220, 226, 190, 154, 118, 82, 46, 47, 48, 49, 43, 37, 31,
         25,
         31, 37, 43, 49, 48, 47, 46, 82, 118, 154, 190, 226, 220, 214, 208, 202};
    return retval;
}

void print_help() {
    PL("USAGE");
    PL("  rnbw [-c|--colors COLORS] [-w|--width WIDTH] [-a|--angle ANGLE] [-p|--path PATH] [-f|--file FILE] [-h|--help]");
    NL;
    PL("DESCRIPTION");
    PL("  TODO");
}

arg_parser_result_t default_res() {
    return {mk_rainbow(), M_PI / 3, 2, "", false};
}

arg_parser_result_t parse_tree(pANTLR3_BASE_TREE tree_arg) {
    arg_parser_result_t retval;

    // defaults
    retval = default_res();
    // retval.width = 2;
    // retval.angle = M_PI / 3;
    // retval.path = mk_rainbow();
    // retval.filename = "";
    // retval.background = false;

    path_sort_t  curr_sort = EDGES;
    path_order_t curr_order = RGB;

    bool colors_opt = false;

    vector<unsigned> path;

    Node tree(tree_arg);
    // PL(tree.str)
    for (unsigned i = 0; i < tree.child_n; ++i) {

        Node option(tree.getChild(i));
        // PL("  " << option.str);
        if (option.str == "COLORS_OPT") {
            colors_opt = true;
            for (unsigned j = 0; j < option.child_n; ++j) {

                Node stripe(option.getChild(j));
                // PL("    " << stripe.str);
                if ((stripe.str == "COLORNUM") || (stripe.str == "COLORNAME")) {
                    path.push_back(get_colornum(stripe));
                } else if (stripe.str == "RANGE") {
                    vector<unsigned> v = parse_range(stripe, curr_sort, curr_order);
                    path.insert(path.end(), v.begin(), v.end());
                }
            }
        } else if (option.str == "PATH_OPT") {
            string sort_str = option.getChild(0).str;
            string order_str = option.getChild(1).str;
            // PL("    " << sort_str << " " << order_str);

            if (sort_str == "DEFAULT_PATH_SORT") {
                curr_sort = EDGES;
            } else {
                curr_sort = str_to_sort(sort_str);
            }

            if (order_str == "DEFAULT_PATH_ORDER") {
                curr_order = RGB;
            } else {
                curr_order = str_to_order(order_str);
            }
        } else if (option.str == "WIDTH_OPT") {
            retval.width = std::stoi(option.getChild(0).str);
            // PL("    " << retval.width);
        } else if (option.str == "ANGLE_OPT") {
            retval.angle = std::stoi(option.getChild(0).str) * M_PI / 180;
            // PL("    " << retval.angle);
        } else if (option.str == "FILE_OPT") {
            // PL("    " << option.getChild(0).str);
            exit(0);
        } else if (option.str == "BACKGROUND_OPT") {
            retval.background = true;
            // PL("    " << true)
        } else if (option.str == "HELP_OPT") {
            print_help();
            exit(0);
        }
    }

    if (colors_opt) {
        retval.path = path;
    }

    return retval;
}

arg_parser_result_t parse_arguments(int argc, char** argv) {
    arg_parser_result_t res;
    if (argc > 1) {

        // PL("argc_0:\n  " << argc);

        string filename = pick_filename(argc, argv);

        // PL("filename:\n  " << filename);
        // PL("argc_1:\n  " << argc);

        char* script = concat(argc, argv);

        // PL("script:\n  " << script);

        antlr_context_t c = get_antlr_context(downcase_cstr(script));
        delete[] script;

        // PL("tree:\n  " << c.ast.tree->toStringTree(c.ast.tree)->chars);

        if (c.ast.tree->getChildCount(c.ast.tree) > 0) {
            res = parse_tree(c.ast.tree);
        } else {
            res = default_res();
        }

        res.filename = filename;
        free_antlr_context(c);
    } else {
        res = default_res();
    }

    return res;
}
