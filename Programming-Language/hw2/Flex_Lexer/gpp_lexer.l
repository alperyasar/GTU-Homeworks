/********************************************************************
*                                                                   *
*                          ALPER YASAR                              *
*                                                                   *
*                           151044072                               *
*                                                                   *
*                   CSE 341 PROGRAMMING LANGUAGES                   *
*                                                                   *
*                    HW1 G++ Language Lexer using flex                 *
*                                                                   *
*******************LEXER FOR FILE IMPLEMENTED CODE*******************
*                                                                   *
*                  >  lex -t gpp_lexer.l > gpp_lexer.c              *
*                  >  gcc gpp_lexer.c                               *
*                  >  ./a.out base.lisp                             *
*                                                                   *
***********************LEXER FOR TERMINAL CODE***********************               
*                                                                   *
*                  >  lex -t gpp_lexer.l > gpp_lexer.c              *
*                  >  gcc gpp_lexer.c                               *
*                  >  ./a.out                                       *
*                                                                   *
*                when enter new line to terminal                    *
*               it will ending code and write to file               *
********************************************************************/

/* Declaring five counters 
* number of lines
* number of characters
 */
%{
int lineNumber = 0;
int charNumber = 0;
int control = 0;
%} 

/***rule 1 counts the number of lines,
rule 2 counts the number of characters
and rule 3 specifies when to stop
taking input***/
%%
and|or|not|equal|less|nil|list|append|concat|set|deffun|for|if|load|disp|true|false {fprintf(yyout, "KEYWORD_%s\n",yytext);lineNumber = 0;}
exit {fprintf(yyout, "KEYWORD_%s\n",yytext); lineNumber = 0;}
;;.*   {fprintf(yyout, "COMMENT\n");lineNumber = 0;}
\"[a-zA-Z0-9]*\"   {fprintf(yyout, "OP_OC\nOP_CC\n");lineNumber = 0;}
[+]   {fprintf(yyout, "OP_PLUS\n");lineNumber = 0;}
[-]   {fprintf(yyout, "OP_MINUS\n");lineNumber = 0;}
[/]   {fprintf(yyout, "OP_DIV\n");lineNumber = 0;lineNumber = 0;}
[*]   {fprintf(yyout, "OP_MULT\n");lineNumber = 0;}
[(]   {fprintf(yyout, "OP_OP\n");lineNumber = 0;}
[)]   {fprintf(yyout, "OP_CP\n");lineNumber = 0;}
[**]+  {fprintf(yyout, "OP_DBLMULT\n");lineNumber = 0;}
[,]   {fprintf(yyout, "OP_COMMA\n");lineNumber = 0;}
[a-zA-Z]+     {fprintf(yyout, "IDENTIFIER \n");lineNumber = 0;}
[0-9]*  {fprintf(yyout, "VALUE\n");lineNumber = 0; }
\n      {if(lineNumber == 0 || control == 1) lineNumber++; else return 0; }
" "     ++charNumber;
.      {fprintf(yyout, "SYNTAX_ERROR\n"); }
%%
int yywrap(){}

int main(int argc, char *argv[]){

    // Explanation:
    // yywrap() - wraps the above rule section
    /* yyin - takes the file pointer
            which contains the input*/
    /* yylex() - this is the main flex function
            which runs the Rule Section*/
    // yytext is the text in the buffer

    // Uncomment the lines below          
    // to take input from file

    if( argc > 1 ) {
        control = 1;
        FILE *fp;
        fp = fopen(argv[1],"r");
        yyin = fp;
    }

    FILE *fpw = fopen("parsed_cpp.txt", "w");
    yyout = fpw;
    yylex();

    return 0;
}
