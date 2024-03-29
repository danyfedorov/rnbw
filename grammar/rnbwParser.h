/** \file
 *  This C header file was generated by $ANTLR version 3.2 debian-16
 *
 *     -  From the grammar source file : rnbw.g
 *     -                            On : 2023-01-14 20:27:05
 *     -                for the parser : rnbwParserParser *
 * Editing it, at least manually, is not wise. 
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser rnbwParser has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 * 
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef prnbwParser, which is returned from a call to rnbwParserNew().
 *
 * The methods in prnbwParser are  as follows:
 *
 *  - rnbwParser_rnbw_return      prnbwParser->rnbw(prnbwParser)
 *  - rnbwParser_clause_return      prnbwParser->clause(prnbwParser)
 *  - rnbwParser_help_opt_return      prnbwParser->help_opt(prnbwParser)
 *  - rnbwParser_colors_opt_return      prnbwParser->colors_opt(prnbwParser)
 *  - rnbwParser_path_opt_return      prnbwParser->path_opt(prnbwParser)
 *  - rnbwParser_width_opt_return      prnbwParser->width_opt(prnbwParser)
 *  - rnbwParser_angle_opt_return      prnbwParser->angle_opt(prnbwParser)
 *  - rnbwParser_file_opt_return      prnbwParser->file_opt(prnbwParser)
 *  - rnbwParser_background_opt_return      prnbwParser->background_opt(prnbwParser)
 *  - rnbwParser_order_return      prnbwParser->order(prnbwParser)
 *  - rnbwParser_path_sort_return      prnbwParser->path_sort(prnbwParser)
 *  - rnbwParser_path_def_return      prnbwParser->path_def(prnbwParser)
 *  - rnbwParser_colors_def_return      prnbwParser->colors_def(prnbwParser)
 *  - rnbwParser_color_delim_return      prnbwParser->color_delim(prnbwParser)
 *  - rnbwParser_color_stripe_return      prnbwParser->color_stripe(prnbwParser)
 *  - rnbwParser_color_range_return      prnbwParser->color_range(prnbwParser)
 *  - rnbwParser_from_to_range_return      prnbwParser->from_to_range(prnbwParser)
 *  - rnbwParser_from_return      prnbwParser->from(prnbwParser)
 *  - rnbwParser_including_clause_return      prnbwParser->including_clause(prnbwParser)
 *  - rnbwParser_not_word_return      prnbwParser->not_word(prnbwParser)
 *  - rnbwParser_to_return      prnbwParser->to(prnbwParser)
 *  - rnbwParser_back_return      prnbwParser->back(prnbwParser)
 *  - rnbwParser_and_word_return      prnbwParser->and_word(prnbwParser)
 *  - rnbwParser_nonverbose_range_return      prnbwParser->nonverbose_range(prnbwParser)
 *  - rnbwParser_lbrace_return      prnbwParser->lbrace(prnbwParser)
 *  - rnbwParser_arrow_return      prnbwParser->arrow(prnbwParser)
 *  - rnbwParser_rbrace_return      prnbwParser->rbrace(prnbwParser)
 *  - rnbwParser_color_return      prnbwParser->color(prnbwParser)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD licence"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_rnbwParser_H
#define _rnbwParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */
 
#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct rnbwParser_Ctx_struct rnbwParser, * prnbwParser;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule 
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif
typedef struct rnbwParser_rnbw_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_rnbw_return;

typedef struct rnbwParser_clause_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_clause_return;

typedef struct rnbwParser_help_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_help_opt_return;

typedef struct rnbwParser_colors_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_colors_opt_return;

typedef struct rnbwParser_path_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_path_opt_return;

typedef struct rnbwParser_width_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_width_opt_return;

typedef struct rnbwParser_angle_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_angle_opt_return;

typedef struct rnbwParser_file_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_file_opt_return;

typedef struct rnbwParser_background_opt_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_background_opt_return;

typedef struct rnbwParser_order_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_order_return;

typedef struct rnbwParser_path_sort_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_path_sort_return;

typedef struct rnbwParser_path_def_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_path_def_return;

typedef struct rnbwParser_colors_def_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_colors_def_return;

typedef struct rnbwParser_color_delim_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_color_delim_return;

typedef struct rnbwParser_color_stripe_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_color_stripe_return;

typedef struct rnbwParser_color_range_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_color_range_return;

typedef struct rnbwParser_from_to_range_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_from_to_range_return;

typedef struct rnbwParser_from_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_from_return;

typedef struct rnbwParser_including_clause_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_including_clause_return;

typedef struct rnbwParser_not_word_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_not_word_return;

typedef struct rnbwParser_to_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_to_return;

typedef struct rnbwParser_back_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_back_return;

typedef struct rnbwParser_and_word_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_and_word_return;

typedef struct rnbwParser_nonverbose_range_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_nonverbose_range_return;

typedef struct rnbwParser_lbrace_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_lbrace_return;

typedef struct rnbwParser_arrow_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_arrow_return;

typedef struct rnbwParser_rbrace_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_rbrace_return;

typedef struct rnbwParser_color_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;
   
}
    rnbwParser_color_return;



/** Context tracking structure for rnbwParser
 */
struct rnbwParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;


     rnbwParser_rnbw_return (*rnbw)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_clause_return (*clause)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_help_opt_return (*help_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_colors_opt_return (*colors_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_path_opt_return (*path_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_width_opt_return (*width_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_angle_opt_return (*angle_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_file_opt_return (*file_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_background_opt_return (*background_opt)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_order_return (*order)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_path_sort_return (*path_sort)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_path_def_return (*path_def)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_colors_def_return (*colors_def)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_color_delim_return (*color_delim)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_color_stripe_return (*color_stripe)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_color_range_return (*color_range)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_from_to_range_return (*from_to_range)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_from_return (*from)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_including_clause_return (*including_clause)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_not_word_return (*not_word)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_to_return (*to)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_back_return (*back)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_and_word_return (*and_word)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_nonverbose_range_return (*nonverbose_range)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_lbrace_return (*lbrace)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_arrow_return (*arrow)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_rbrace_return (*rbrace)	(struct rnbwParser_Ctx_struct * ctx);
     rnbwParser_color_return (*color)	(struct rnbwParser_Ctx_struct * ctx);
    // Delegated rules
    const char * (*getGrammarFileName)();
    void	    (*free)   (struct rnbwParser_Ctx_struct * ctx);
    /* @headerFile.members() */
    pANTLR3_BASE_TREE_ADAPTOR	adaptor;
    pANTLR3_VECTOR_FACTORY		vectors;
    /* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API prnbwParser rnbwParserNew         (pANTLR3_COMMON_TOKEN_STREAM instream);
ANTLR3_API prnbwParser rnbwParserNewSSD      (pANTLR3_COMMON_TOKEN_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the parser will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif 
#define DEFAULT_INCLUDING      18
#define T__50      50
#define T__59      59
#define DEFAULT_PATH_ORDER      19
#define T__55      55
#define T__56      56
#define T__57      57
#define T__58      58
#define INCLUDING      16
#define ID      23
#define T__51      51
#define T__52      52
#define T__53      53
#define T__54      54
#define T__60      60
#define T__61      61
#define COLORS_OPT      6
#define BACKGROUND_OPT      10
#define HELP_OPT      5
#define T__26      26
#define TOP      4
#define PATH_OPT      7
#define T__27      27
#define T__28      28
#define T__29      29
#define T__24      24
#define T__25      25
#define T__62      62
#define RANGE      13
#define INT      21
#define NOT_INCLUDING      17
#define T__37      37
#define T__38      38
#define T__39      39
#define T__33      33
#define T__34      34
#define T__35      35
#define T__36      36
#define WS      22
#define EOF      -1
#define T__30      30
#define T__31      31
#define T__32      32
#define WIDTH_OPT      8
#define COLORNUM      11
#define NO_BACK      15
#define T__48      48
#define T__49      49
#define T__44      44
#define ANGLE_OPT      9
#define COLORNAME      12
#define DEFAULT_PATH_SORT      20
#define T__45      45
#define BACK      14
#define T__46      46
#define T__47      47
#define T__40      40
#define T__41      41
#define T__42      42
#define T__43      43
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for rnbwParser
 * =============================================================================
 */
/** \} */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
