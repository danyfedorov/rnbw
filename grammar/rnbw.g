grammar rnbw;

options
{
    language = C;
    output = AST;
    backtrack = true;
    ASTLabelType = pANTLR3_BASE_TREE;
}

tokens
{
    TOP;

    COLORS_OPT;
    PATH_OPT;
    WIDTH_OPT;
    ANGLE_OPT;

    // COLORS_OPT
    COLORNUM;
    COLORNAME;
    RANGE;
    BACK;
    NO_BACK;

    INCLUDING;
    NOT_INCLUDING;
    DEFAULT_INCLUDING;

    // PATH_OPT
    DEFAULT_PATH_ORDER;
    DEFAULT_PATH_SORT;

}

rnbw: clause* -> ^(TOP clause*) ;

clause:
        colors_opt colors_def -> ^(COLORS_OPT colors_def)
	|	path_opt   path_def   -> ^(PATH_OPT   path_def)
	|	width_opt  INT        -> ^(WIDTH_OPT  INT)
	|	angle_opt  INT        -> ^(ANGLE_OPT  INT) ;

colors_opt:	'-c' | '--colors' ;
path_opt:	'-p' | '--path'   ;
width_opt:	'-w' | '--width'  ;
angle_opt:	'-a' | '--angle'  ;

order:
      'rgb'
    | 'rbg'
    | 'grb'
    | 'gbr'
    | 'brg'
    | 'bgr'
    | -> DEFAULT_PATH_ORDER ;

path_sort:
      'line'
    | 'yarn'
    | 'edges'
    | -> DEFAULT_PATH_SORT ;

path_def: path_sort order;

colors_def:	color_stripe (color_delim? color_stripe)* -> color_stripe+;

color_delim: WS | ',' ;

color_stripe:
      color
    | color_range ;

color_range:
      from_to_range
    | nonverbose_range ;

from_to_range: from color to color back -> ^(RANGE from color to color back) ;

from:
      'from' including_clause -> including_clause
    |                         -> DEFAULT_INCLUDING;

including_clause:
      'including'          -> INCLUDING
    | not_word 'including' -> NOT_INCLUDING
    |                      -> DEFAULT_INCLUDING ;

not_word: 'not' | '!' ;

to: 'to' including_clause -> including_clause ;

back:
      and_word? 'back' including_clause -> ^(BACK including_clause)
    |                                   -> NO_BACK;

and_word: 'and' ;

nonverbose_range: lbrace color arrow color rbrace -> ^(RANGE lbrace color rbrace color arrow);

lbrace:
      '(' -> NOT_INCLUDING
    | '[' -> INCLUDING
    |     -> DEFAULT_INCLUDING ;

arrow:
      '->'  ->
    | '<->' -> ^(BACK DEFAULT_INCLUDING)
    | '<i>' -> ^(BACK INCLUDING)
    | '<n>' -> ^(BACK NOT_INCLUDING) ;

rbrace:
      ')' -> NOT_INCLUDING
    | ']' -> INCLUDING
    |     -> DEFAULT_INCLUDING ;

color:
      ID  -> ^(COLORNAME  ID)
    | INT -> ^(COLORNUM   INT) ;

// L

ID:	('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'0'..'9'|'-')*
    ;

INT: '0'..'9'+
    ;

WS: ( ' '
    | '\t'
    | '\r'
    | '\n'
    ) {$channel=HIDDEN;}
    ;
