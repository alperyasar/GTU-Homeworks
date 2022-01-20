program(FunctionList) :-
  functionList(FunctionList).

functionList([Function, FunctionListCollection]) :-
  function(Function),
  functionListCollection(FunctionListCollection).

functionListCollection(FunctionListCollection) :-
  functionList(FunctionListCollection).
functionListCollection([]) :-
  [].

function([TypeID, '(', TypeIDList, ')', '=', Expression]) :-
  typeID(TypeID),
  ['OPEN_P'],
  typeIDList(TypeIDList),
  ['CLOSE_P', 'ASSIGN'],
  expression(Expression).

typeID(['int', 'id']) :-
  ['TYPE_INT', 'ID'].
typeID(['bool', 'id']) :-
  ['TYPE_BOOL', 'ID'].

typeIDList([TypeID, TypeIDListCollection]) :-
  typeID(TypeID),
  typeIDListCollection(TypeIDListCollection).

typeIDListCollection([',', TypeIDList]) :-
  ['COMMA'],
  typeIDList(TypeIDList).
typeIDListCollection([]) :-
  [].

expression(['if', Comparison, 'then', ValueTrue, 'else', ValueFalse]) :-
  ['COND_IF'],
  comparison(Comparison),
  ['COND_THEN'],
  value(ValueTrue),
  ['COND_ELSE'],
  value(ValueFalse).
expression(['let', 'id', '=', Value, 'in', Expression]) :-
  ['LET', 'ID', 'ASSIGN'],
  value(Value),
  ['LET_IN'],
  expression(Expression).
expression([Value, Expression]) :-
  value(Value),
  extraExpression(Expression).

extraExpression([Arithmetic]) :-
  arithmetic(Arithmetic).
extraExpression([]) :-
  [].

arithmetic(['+', Value]) :-
  ['ARITH_ADD'],
  value(Value).
arithmetic(['-', Value]) :-
  ['ARITH_SUB'],
  value(Value).
arithmetic(['*', Value]) :-
  ['ARITH_MUL'],
  value(Value).
arithmetic(['/', Value]) :-
  ['ARITH_DIV'],
  value(Value).
arithmetic(['#', Value]) :-
  ['ARITH_MOD'],
  value(Value).
  
# lexer/2
# lexer(+TokenList, -LexedList).
# Takes in a list of tokens and returns a list of lexemes (i.e., abstract units
# defining the meaning of the token)
lexer([], []).
lexer([Token|TokenList], [Lexeme|LexedList]) :-
  lex_token(Token, Lexeme),
  lexer(TokenList, LexedList).

# lex_token/2
# lex_token(+Token, -Lexeme)
# Definitions of the rules used to creating the lexeme list
lex_token('int',  'TYPE_INT').
lex_token('bool', 'TYPE_BOOL').
lex_token(',',    'COMMA').
lex_token('=',    'ASSIGN').
lex_token('let',  'LET').
lex_token('in',   'LET_IN').
lex_token('if',   'COND_IF').
lex_token('then', 'COND_THEN').
lex_token('else', 'COND_ELSE').
lex_token('==',   'RELAT_EQ').
lex_token('!=',   'RELAT_NOT_EQ').
lex_token('>',    'RELAT_GT').
lex_token('>=',   'RELAT_GTEQ').
lex_token('<',    'RELAT_LT').
lex_token('<=',   'RELAT_LTEQ').
lex_token('+',    'ARITH_ADD').
lex_token('-',    'ARITH_SUB').
lex_token('*',    'ARITH_MUL').
lex_token('/',    'ARITH_DIV').
lex_token('#',    'ARITH_MOD').
lex_token('(',    'OPEN_P').
lex_token(')',    'CLOSE_P').
lex_token(Number, 'INTEGER') :-
  atom_number(Number, Integer),
  integer(Integer).
lex_token(_,      'ID').

comparison([Value, Comparison]) :-
  value(Value),
  comparisonRight(Comparison).

comparisonRight(['==', Value]) :-
  ['RELAT_EQ'],
  value(Value).
comparisonRight(['!=', Value]) :-
  ['RELAT_NOT_EQ'],
  value(Value).
comparisonRight(['>', Value]) :-
  ['RELAT_GT'],
  value(Value).
comparisonRight(['>=', Value]) :-
  ['RELAT_GTEQ'],
  value(Value).
comparisonRight(['<', Value]) :-
  ['RELAT_LT'],
  value(Value).
comparisonRight(['<=', Value]) :-
  ['RELAT_LTEQ'],
  value(Value).

value([integer]) :-
  ['INTEGER'].
value(['id', ValueParameters]) :-
  ['ID'],
  valueParameters(ValueParameters).

valueParameters(['(', Parameters, ')']) :-
  ['OPEN_P'],
  parameters(Parameters),
  ['CLOSE_P'].
valueParameters([]) :-
  [].

parameters([Value, ParametersList]) :-
  value(Value),
  parametersList(ParametersList).

parametersList([',', Parameters]) :-
  ['COMMA'],
  parameters(Parameters).
parametersList([]) :-
  [].


# Takes in a filename, returns the file contents as a list of tokens
tokenize_file(FileName, token_List) :-
  write("alper"),
  open(FileName, read, Stream),
  read_tokens_from_stream(Stream, Tokens_From_Stream),
  close(Stream),
  clean_token_list(Tokens_From_Stream, Token_List).

# read_tokens_from_stream/2
# read_tokens_from_stream(+Stream, -Tokens_From_Stream)
# Tokens are read from a stream and added to a list
read_tokens_from_stream(Stream, [Token|Tokens_From_Stream]) :-
  \+ at_end_of_stream(Stream),
  get_next_token(Stream, Token),
  !,
  read_tokens_from_stream(Stream, Tokens_From_Stream).
read_tokens_from_stream(_, []).

# get_next_token/2
# get_next_token(+Stream, -Token).
# Reads characters from stream and unifies as a single token
get_next_token(Stream, Token) :-
  get0(Stream, Ascii_Char),
  get_next_char(Stream, String, Ascii_Char),
  atom_codes(Token, String).

# get_next_char/3
# get_next_char(+Stream, -String, +Ascii_Char).
# Retrieves the next character from the stream unless it has an ASCII code 
# below 32 (i.e., whitespace or control character)
get_next_char(Stream, [Ascii_Char|String], Ascii_Char) :-
  Ascii_Char > 32,
  get0(Stream, Next_Ascii_Char),
  !,
  get_next_char(Stream, String, Next_Ascii_Char).
get_next_char(_, [], _).

# clean_token_list/2
# clean_token_list(+Tokens_From_Stream, -Token_List).
# Removes empty tokens generated by consecutive whitespace delimiters
clean_token_list([], []) :-
  !.
clean_token_list([''|Tokens_From_Stream], Token_List) :-
  !,
  clean_token_list(Tokens_From_Stream, Token_List).
clean_token_list([Token|Tokens_From_Stream], [Token|Token_List]) :-
  clean_token_list(Tokens_From_Stream, Token_List).

  # parse_list/2
# parse_list(+LexedList, -StructuredList)
# Creates the StructuredList from the LexedList
parse_list(LexedList, StructuredList) :-
  phrase(program(StructuredList), LexedList, []).

# clean_parsed_list/3
# clean_parsed_list(TokenList, StructuredList, ParsedList)
# Simplifies the call for the clean_parsed_list/4 predicate which uses an extra
# variable for handling the token list
clean_parsed_list(TokenList, StructuredList, ParsedList) :-
  clean_parsed_list(TokenList, StructuredList, ParsedList, _).

# clean_parsed_list/4
# clean_parsed_list(TokenList, StructuredList, ParsedList, ).
# Recurses through structured list and replaces lexeme types with their
# corresponding token
clean_parsed_list(TokenList, [], [], TokenList).
clean_parsed_list(TokenList, [Head|StructuredList], [Parse|ParsedList],
                  NewTokenList) :-
  is_list(Head),
  clean_parsed_list(TokenList, Head, Parse, RemainingTokens),
  clean_parsed_list(RemainingTokens, StructuredList, ParsedList, NewTokenList).
clean_parsed_list([Token|TokenList], [_|StructuredList], [Token|ParsedList],
                  NewTokenList) :-
  clean_parsed_list(TokenList, StructuredList, ParsedList, NewTokenList).

# parse_token_list/2
# parse_token_list(TokenList, ParsedList).
# Simplifies creating the parsed list by wrapping other predicates
parse_token_list(TokenList, ParsedList) :-
  lexer(TokenList, LexedList),
  parse_list(LexedList, StructuredList),
  clean_parsed_list(TokenList, StructuredList, ParsedList).


program(FunctionList) :-
  functionList(FunctionList).

functionList([Function, FunctionListCollection]) :-
  function(Function),
  functionListCollection(FunctionListCollection).

functionListCollection(FunctionListCollection) :-
  functionList(FunctionListCollection).
functionListCollection([]) :-
  [].

function([TypeID, '(', TypeIDList, ')', '=', Expression]) :-
  typeID(TypeID),
  ['OPEN_P'],
  typeIDList(TypeIDList),
  ['CLOSE_P', 'ASSIGN'],
  expression(Expression).

typeID(['int', 'id']) :-
  ['TYPE_INT', 'ID'].
typeID(['bool', 'id']) :-
  ['TYPE_BOOL', 'ID'].

typeIDList([TypeID, TypeIDListCollection]) :-
  typeID(TypeID),
  typeIDListCollection(TypeIDListCollection).

typeIDListCollection([',', TypeIDList]) :-
  ['COMMA'],
  typeIDList(TypeIDList).
typeIDListCollection([]) :-
  [].

expression(['if', Comparison, 'then', ValueTrue, 'else', ValueFalse]) :-
  ['COND_IF'],
  comparison(Comparison),
  ['COND_THEN'],
  value(ValueTrue),
  ['COND_ELSE'],
  value(ValueFalse).
expression(['let', 'id', '=', Value, 'in', Expression]) :-
  ['LET', 'ID', 'ASSIGN'],
  value(Value),
  ['LET_IN'],
  expression(Expression).
expression([Value, Expression]) :-
  value(Value),
  extraExpression(Expression).

extraExpression([Arithmetic]) :-
  arithmetic(Arithmetic).
extraExpression([]) :-
  [].

arithmetic(['+', Value]) :-
  ['ARITH_ADD'],
  value(Value).
arithmetic(['-', Value]) :-
  ['ARITH_SUB'],
  value(Value).
arithmetic(['*', Value]) :-
  ['ARITH_MUL'],
  value(Value).
arithmetic(['/', Value]) :-
  ['ARITH_DIV'],
  value(Value).
arithmetic(['%', Value]) :-
  ['ARITH_MOD'],
  value(Value).

comparison([Value, Comparison]) :-
  value(Value),
  comparisonRight(Comparison).

comparisonRight(['==', Value]) :-
  ['RELAT_EQ'],
  value(Value).
comparisonRight(['!=', Value]) :-
  ['RELAT_NOT_EQ'],
  value(Value).
comparisonRight(['>', Value]) :-
  ['RELAT_GT'],
  value(Value).
comparisonRight(['>=', Value]) :-
  ['RELAT_GTEQ'],
  value(Value).
comparisonRight(['<', Value]) :-
  ['RELAT_LT'],
  value(Value).
comparisonRight(['<=', Value]) :-
  ['RELAT_LTEQ'],
  value(Value).

value([integer]) :-
  ['INTEGER'].
value(['id', ValueParameters]) :-
  ['ID'],
  valueParameters(ValueParameters).

valueParameters(['(', Parameters, ')']) :-
  ['OPEN_P'],
  parameters(Parameters),
  ['CLOSE_P'].
valueParameters([]) :-
  [].

parameters([Value, ParametersList]) :-
  value(Value),
  parametersList(ParametersList).

parametersList([',', Parameters]) :-
  ['COMMA'],
  parameters(Parameters).
parametersList([]) :-
  [].

main() :-
  write_parser("input.txt","output.txt").

write_parser(InputFileName, OutputFile) :-  
  tokenize_file(InputFileName, TokenList), 
  lexer(TokenList, LexedList), 
  write_output_to_file(OutputFile, TokenList).


write_output_to_file(OutputFile, List) :-
  open(OutputFile, write, Stream),
  write(Stream, List),
  close(Stream), !.