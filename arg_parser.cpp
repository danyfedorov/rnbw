#include "arg_parser.h"

// internal
#include "core.h"
#include "clrs.h"

// std
#include <string>
#include <cstring>
#include <stdexcept>
#include <assert.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using std::string;
using std::vector;

using std::cout;
using std::endl;

antlr_context_t get_antlr_context(char* input_arg) {

    pANTLR3_INPUT_STREAM input = antlr3NewAsciiStringCopyStream((pANTLR3_UINT8)input_arg, (ANTLR3_UINT32)strlen(input_arg), NULL);

    prnbwLexer lxr;
    pANTLR3_COMMON_TOKEN_STREAM tstream;
    prnbwParser psr;
    rnbwParser_rnbw_return rnbwAST;

    lxr = rnbwLexerNew(input);

    if (lxr == NULL) {
        fprintf(stderr, "Unable to create the lexer due to malloc() failure1\n");
        exit(ANTLR3_ERR_NOMEM);
    }

    tstream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lxr));

    if (tstream == NULL) {
        fprintf(stderr, "Out of memory trying to allocate token stream\n");
        exit(ANTLR3_ERR_NOMEM);
    }

    psr = rnbwParserNew(tstream);

    if (tstream == NULL) {
        fprintf(stderr, "Out of memory trying to allocate parser\n");
        exit(ANTLR3_ERR_NOMEM);
    }

    rnbwAST = psr->rnbw(psr);

    if (psr->pParser->rec->state->errorCount > 0) {
        fprintf(stderr, "The parser returned %d errors, tree walking aborted.\n", psr->pParser->rec->state->errorCount);
        throw std::runtime_error("parser err");
    }
    // else {
    //     printf("1 Tree : %s\n", rnbwAST.tree->toStringTree(rnbwAST.tree)->chars);
    // }

    return (antlr_context_t){input, lxr, tstream, psr, rnbwAST};
}

void free_antlr_context_mem(antlr_context_t a) {
    a.psr     ->free  (a.psr);      a.psr = NULL;
    a.tstream ->free  (a.tstream);	a.tstream = NULL;
    a.lxr	    ->free  (a.lxr);	    a.lxr = NULL;
    a.input   ->close (a.input);	  a.input = NULL;
}

unsigned getsize(int argc, char** argv) {
    unsigned size = 0;
    for (int i = 1; i < argc; ++i) {
        size += strlen(argv[i]) + 1;
    }
    return size;
}

char* concat(int argc, char** argv) {
    unsigned size = getsize(argc, argv);

    char* retval = new char[size + 1]; // +1 for \0
    strcpy(retval, argv[1]);
    strcat(retval, " ");
    for (int i = 2; i < argc; ++i) {
        strcat(retval, argv[i]);
        strcat(retval, " ");
    }
    return retval;
}

arg_parser_result_t mk_fake_res() {
    arg_parser_result_t retval;

    retval.path.push_back(196);
    retval.path.push_back(208);
    retval.path.push_back(220);
    retval.path.push_back(255);

    retval.angle = 0;
    retval.width = 1;

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

arg_parser_result_t parse_tree(pANTLR3_BASE_TREE tree_arg) {
    arg_parser_result_t retval;

    path_sort_t  curr_sort;
    path_order_t curr_order;

    Node tree(tree_arg);

    for (unsigned i = 0; i < tree.child_n; ++i) {
        Node option(tree.getChild(i));

        cout << option.str << endl;

        if (option.str == "COLORS_OPT") {

            for (unsigned j = 0; j < option.child_n; ++j) {
                Node stripe(option.getChild(j));

                cout << "  " << stripe.str << endl;

                if (stripe.str == "COLORNUM") {

                } else if (stripe.str == "COLORNAME") {

                } else if (stripe.str == "RANGE") {
                    string from_including = stripe.getChild(0).str;
                    Node   from_color(stripe.getChild(1));

                    string to_including = stripe.getChild(2).str;
                    Node   to_color(stripe.getChild(3));

                    string back = stripe.getChild(4).str;

                    cout << "    " << from_including <<  " " << from_color.str << endl;
                    cout << "    " << to_including <<  " " << to_color.str << endl;
                    cout << "    " << back << endl;



                }
            }
        } else if (option.str == "PATH_OPT") {
            string sort = option.getChild(0).str;
            string order = option.getChild(1).str;

            cout << "  " << sort << " " << order << endl;
        } else if (option.str == "WIDTH_OPT") {

        } else if (option.str == "ANGLE_OPT") {

        }
    }

    return retval;
}

arg_parser_result_t parse_arguments(int argc, char** argv) {
    char* script = concat(argc, argv);
    antlr_context_t c = get_antlr_context(downcase_cstr(script));
    delete[] script;

    printf("2 Tree : %s\n", c.ast.tree->toStringTree(c.ast.tree)->chars);
    parse_tree(c.ast.tree);

    free_antlr_context_mem(c);
    return mk_fake_res();
}
