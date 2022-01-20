            FILE *fo;
/********************************************************************
*                                                                   *
*                          ALPER YASAR                              *
*                                                                   *
*                           151044072                               *
*                                                                   *
*                   CSE 341 PROGRAMMING LANGUAGES                   *
*                                                                   *
*                 HW3 G++ Language Syntax Analyzer                  *
*                                                                   *
*******************LEXER FOR FILE IMPLEMENTED CODE*******************
*                                                                   *
*                  >  make                                          *
*                  >  ./a.out base.lisp                             *
*                                                                   *
***********************LEXER FOR TERMINAL CODE***********************               
*                                                                   *
*                  >  make                                          *
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
int defunControl = 0;
int openPh = 0;    //when a brackets is open increase it.
int phCheck = 0;   //needs to use open brackets before some special keywords. it checks it. if did not give error.
int errorCheck = 0;

char **id; //hold variable names
int idSize = 1;
%} 

/***rule 1 counts the number of lines,
rule 2 counts the number of characters
and rule 3 specifies when to stop
taking input***/                                                                  
%%
and|or|not|equal|list|append|for|if|load {
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"%s\" \n",yytext);
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    phCheck = 0;
    fputs(yytext,yyout);
    fprintf(yyout, " ");
    lineNumber = 0;
}
less { 
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"<\" \n"); 
        errorCheck=1; 
        return 0;
    }
    fprintf(fo, "KEYWORD_%s\n",yytext); 
    phCheck = 0; 
    fprintf(yyout, "< "); 
    lineNumber = 0;
}
concat { 
    if(phCheck == 0){
    printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"concat\" \n"); 
    errorCheck=1; 
    return 0;
    } 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    phCheck = 0; 
    fprintf(yyout, "concatenate "); 
    lineNumber = 0;
}
set { 
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"set\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    phCheck = 0; 
    fprintf(yyout, "set "); 
    lineNumber = 0; 
    defunControl = 1;
}
deffun { 
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"defun\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    phCheck = 0; 
    fprintf(yyout, "defun "); 
    lineNumber = 0; 
    defunControl = 1;
}
true { 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    fprintf(yyout, "t "); 
    lineNumber = 0;
}
false { 
    fprintf(fo, "KEYWORD_%s\n",yytext);
    fprintf(yyout, "nil "); 
    lineNumber = 0;
}
;;.*   {
    fprintf(fo, "KEYWORD_%s\n",yytext);
    fprintf(yyout, "COMMENT\n");
    lineNumber = 0;
}
nil {
    fprintf(fo, "KEYWORD_%s\n",yytext);
    fputs(yytext,yyout);
    fprintf(yyout, " ");
    lineNumber = 0;
}
\"[a-zA-Z0-9]*\"   {
    fprintf(fo, "OP_OC\nOP_CC\n");
    fprintf(yyout, "OP_OC\nOP_CC\n");
    lineNumber = 0; 
}
[+]   {
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"+\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "OP_PLUS\n");
    phCheck = 0; 
    fprintf(yyout, "+ ");
    lineNumber = 0;
}
[-]   {
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"-\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "OP_MINUS\n");   
    phCheck = 0; 
    fprintf(yyout, "- ");
    lineNumber = 0;
}
[/]   {
    if(phCheck == 0){printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"/\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "OP_DIV\n");  
    phCheck = 0; 
    fprintf(yyout, "/ ");
    lineNumber = 0;
}
[*]   {
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"*\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    fprintf(fo, "OP_MULT\n");  
    phCheck = 0; 
    fprintf(yyout, "* ");
    lineNumber = 0;
}
[(]   {
    fprintf(fo, "OP_OP\n");  
    fprintf(yyout, "( ");
    lineNumber = 0; 
    openPh++; 
    phCheck = 1;
}
[)]   {
    fprintf(fo, "OP_CP\n");  
    fprintf(yyout, ") ");
    lineNumber = 0; openPh--; 
    if(defunControl == 1) defunControl = 0;
}
[**]+  {
    fprintf(fo, "OP_DBLMULT\n");  
    if(phCheck == 0){
        printf ("SYNTAX_ERROR miss open brackets before KEYWORDS \"**\" \n"); 
        errorCheck=1; 
        return 0;
    } 
    phCheck = 0; 
    fprintf(yyout, "** ");
    lineNumber = 0;
}
[,]   {
    fprintf(fo, "OP_COMMA\n");  
    fprintf(yyout, ", ");
    lineNumber = 0;
}
[a-zA-Z]+     {
    fprintf(fo, "IDENTIFIER\n");  
    fputs(yytext,yyout);
    fprintf(yyout, " ");
    lineNumber = 0;
    if(defunControl == 1){
        for(int i = 0; i<idSize-1 && idSize > 1;i++){
            if(strcmp(yytext,id[i]) == 0){
                printf ("SYNTAX_ERROR This \"%s\" variable is declared before  \n",yytext); 
                errorCheck=1; 
                return 0;
            }
        }
        if(idSize == 1) id =(char **) malloc(idSize * sizeof(char *) );
        else  id =(char **) realloc(id, idSize * sizeof(char *) );
        id[idSize-1] = (char *)malloc(25 * sizeof(char) );
        strcpy(id[idSize-1],yytext);
        idSize++;    
    }
    else {
        int k=0;
        for(int i = 0; i<idSize-1 && idSize > 1;i++){
            if(strcmp(yytext,id[i]) == 0){
                k = 1;
            }
        }
        if(k==0){
            printf ("SYNTAX_ERROR This \"%s\" variable is not declared before  \n",yytext); 
            errorCheck=1; 
            return 0;
        }
        
    }
}
[0-9]*  {
    fprintf(fo, "VALUE\n");  
    fputs(yytext,yyout);
    fprintf(yyout, " ");
    lineNumber = 0; 
}
\n      {
    if(lineNumber == 0 || control == 1) lineNumber++; 
        else return 0; 
}
" "     ++charNumber;
.      {
    fprintf(fo, "SYNTAX_ERROR\n");  
    fprintf(yyout, "SYNTAX_ERROR\n"); 
}
%%

int yywrap(){}
#include <string.h>
#include <stdlib.h>
#include <string.h>
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
    fo = fopen("parsed_cpp.txt", "w");
    FILE *fpw = fopen("temp.lisp", "a+");
    yyout = fpw;


    fprintf(yyout, "(defun tempFunc () ");
    yylex();
    fprintf(yyout, ") (format t \"Result: \") (write (tempFunc)) "); 
    
    for(int i=0;i<idSize-1 && idSize > 1;i++){
        free(id[i]);
    }   
    fclose (fpw);
    if (openPh > 0 && errorCheck == 0){
        printf("SYNTAX_ERROR miss close brackets \n");
        return 0;
    }
    if(!errorCheck){
        printf("Syntax OK.\n"); 
        char cmd[255] = "", **p;
        strcpy(cmd,"clisp temp.lisp");
        system(cmd);
        remove("temp.lisp");
    }


    return 0;
}